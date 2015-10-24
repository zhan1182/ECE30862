package com.brackeen.javagamebook.tilegame;

import java.awt.*;
import java.awt.event.KeyEvent;
import java.util.Iterator;
import javax.sound.midi.Sequence;
import javax.sound.midi.Sequencer;


import com.brackeen.javagamebook.graphics.*;
import com.brackeen.javagamebook.sound.*;
import com.brackeen.javagamebook.input.*;
import com.brackeen.javagamebook.tilegame.sprites.*;
import com.brackeen.javagamebook.state.*;

public class MainGameState implements GameState {

    private static final int DRUM_TRACK = 1;

    public static final float GRAVITY = 0.002f;

    private SoundManager soundManager;
    private MidiPlayer midiPlayer;
    private TileGameResourceManager resourceManager;
    private int width;
    private int height;
    private int offsetX;
    
    private Point pointCache = new Point();
    private Sound prizeSound;
    private Sound boopSound;
    private Sequence music;
    private TileMap map;
    private TileMapRenderer renderer;

    private String stateChange;
    private boolean move = false;

    private GameAction moveLeft;
    private GameAction moveRight;
    private GameAction jump;
    private GameAction exit;
    private GameAction shoot;//!!!Init Shoot Action


    public MainGameState(SoundManager soundManager,
        MidiPlayer midiPlayer, int width, int height)
    {
        this.soundManager = soundManager;
        this.midiPlayer = midiPlayer;
        this.width = width;
        this.height = height;
        moveLeft = new GameAction("moveLeft");
        moveRight = new GameAction("moveRight");
        jump = new GameAction("jump",
            GameAction.DETECT_INITAL_PRESS_ONLY);
        exit = new GameAction("exit",
            GameAction.DETECT_INITAL_PRESS_ONLY);
        shoot = new GameAction("shoot",
                               GameAction.DETECT_INITAL_PRESS_ONLY);//!!!
        renderer = new TileMapRenderer();
        toggleDrumPlayback();
    }

    public String getName() {
        return "Main";
    }


    public String checkForStateChange() {
        return stateChange;
    }

    public void loadResources(ResourceManager resManager) {

        resourceManager = (TileGameResourceManager)resManager;

        resourceManager.loadResources();

        renderer.setBackground(
            resourceManager.loadImage("background.png"));

        // load first map
        map = resourceManager.loadNextMap();

        // load sounds
        prizeSound = resourceManager.loadSound("sounds/prize.wav");
        boopSound = resourceManager.loadSound("sounds/boop2.wav");
        music = resourceManager.loadSequence("sounds/music.midi");
    }

    public void start(InputManager inputManager) {
        inputManager.mapToKey(moveLeft, KeyEvent.VK_LEFT);
        inputManager.mapToKey(moveRight, KeyEvent.VK_RIGHT);
        inputManager.mapToKey(jump, KeyEvent.VK_SPACE);
        inputManager.mapToKey(jump, KeyEvent.VK_UP);
        inputManager.mapToKey(exit, KeyEvent.VK_ESCAPE);
        inputManager.mapToKey(shoot, KeyEvent.VK_S);//!!!
        soundManager.setPaused(false);
        midiPlayer.setPaused(false);
        midiPlayer.play(music, true);
        toggleDrumPlayback();
    }

    public void stop() {
        soundManager.setPaused(true);
        midiPlayer.setPaused(true);
    }


    public void draw(Graphics2D g) {
        renderer.draw(g, map, width, height);
    }


    /**
        Turns on/off drum playback in the midi music (track 1).
    */
    public void toggleDrumPlayback() {
        Sequencer sequencer = midiPlayer.getSequencer();
        if (sequencer != null) {
            sequencer.setTrackMute(DRUM_TRACK,
                !sequencer.getTrackMute(DRUM_TRACK));
        }
    }

    private void checkInput(long elapsedTime) {

        if (exit.isPressed()) {
            stateChange = GameStateManager.EXIT_GAME;
            return;
        }

        Player player = (Player)map.getPlayer();
        if (player.isAlive()) {
            float velocityX = 0;
            if (moveLeft.isPressed()) {
                velocityX-=player.getMaxSpeed();
                move = true;
            }
            if (moveRight.isPressed()) {
                velocityX+=player.getMaxSpeed();
                move = true;
            }
            if (jump.isPressed()) {
                player.jump(false);
            }
            if(shoot.isPressed()){
            	int currFstate = player.getFstate();
            	if(currFstate == 0){
            		player.setFstate(1);
            		player.setTimer(player.getFirerate());
            	}else if(currFstate == 1){
            		player.setFstate(2);
            		player.setTimer(player.getFirerate() * 10);
            	}
            }
            player.setVelocityX(velocityX);
        }

    }


    /**
        Gets the tile that a Sprites collides with. Only the
        Sprite's X or Y should be changed, not both. Returns null
        if no collision is detected.
    */
    public Point getTileCollision(Sprite sprite,
        float newX, float newY)
    {
        float fromX = Math.min(sprite.getX(), newX);
        float fromY = Math.min(sprite.getY(), newY);
        float toX = Math.max(sprite.getX(), newX);
        float toY = Math.max(sprite.getY(), newY);

        // get the tile locations
        int fromTileX = TileMapRenderer.pixelsToTiles(fromX);
        int fromTileY = TileMapRenderer.pixelsToTiles(fromY);
        int toTileX = TileMapRenderer.pixelsToTiles(
            toX + sprite.getWidth() - 1);
        int toTileY = TileMapRenderer.pixelsToTiles(
            toY + sprite.getHeight() - 1);

        // check each tile for a collision
        for (int x=fromTileX; x<=toTileX; x++) {
            for (int y=fromTileY; y<=toTileY; y++) {
                if (x < 0 || x >= map.getWidth() ||
                    map.getTile(x, y) != null)
                {
                    // collision found, return the tile
                    pointCache.setLocation(x, y);
                    return pointCache;
                }
            }
        }

        // no collision found
        return null;
    }


    /**
        Checks if two Sprites collide with one another. Returns
        false if the two Sprites are the same. Returns false if
        one of the Sprites is a Creature that is not alive.
    */
    public boolean isCollision(Sprite s1, Sprite s2) {
        // if the Sprites are the same, return false
        if (s1 == s2) {
            return false;
        }

        // if one of the Sprites is a dead Creature, return false
        if (s1 instanceof Creature && !((Creature)s1).isAlive()) {
            return false;
        }
        if (s2 instanceof Creature && !((Creature)s2).isAlive()) {
            return false;
        }

        // get the pixel location of the Sprites
        int s1x = Math.round(s1.getX());
        int s1y = Math.round(s1.getY());
        int s2x = Math.round(s2.getX());
        int s2y = Math.round(s2.getY());

        // check if the two sprites' boundaries intersect
        return (s1x < s2x + s2.getWidth() &&
            s2x < s1x + s1.getWidth() &&
            s1y < s2y + s2.getHeight() &&
            s2y < s1y + s1.getHeight());
    }


    /**
        Gets the Sprite that collides with the specified Sprite,
        or null if no Sprite collides with the specified Sprite.
    */
    public Sprite getSpriteCollision(Sprite sprite) {

        // run through the list of Sprites
        Iterator i = map.getSprites();
        while (i.hasNext()) {
            Sprite otherSprite = (Sprite)i.next();
            if (isCollision(sprite, otherSprite)) {
                // collision found, return the Sprite
                return otherSprite;
            }
        }

        // no collision found
        return null;
    }


    /**
        Updates Animation, position, and velocity of all Sprites
        in the current map.
    */
    public void update(long elapsedTime) {
        Creature player = (Creature)map.getPlayer();


        // player is dead! start map over
        if (player.getState() == Creature.STATE_DEAD) {
            map = resourceManager.reloadMap();
            return;
        }

        // get keyboard/mouse input
        checkInput(elapsedTime);
        int currTimer = player.getTimer();
        int fstate = player.getFstate();
        if ((fstate == 1 || fstate == 2) && currTimer > 0 && (currTimer % player.getFirerate() == 0)){
        	Bullet bullet1 = (Bullet)resourceManager.getBullet1().clone();
        	bullet1.setX(player.getX());
        	bullet1.setY(player.getY());
        	bullet1.setTarget(0);
        	if(player.getDirection()){
        		bullet1.setVelocityX(bullet1.getSpeed1());
        	}else{
        		bullet1.setVelocityX(-bullet1.getSpeed1());
        	}
        	map.addSprite(bullet1);
        }
        // update player
        updateCreature(player, elapsedTime);
        player.update(elapsedTime);
        // update other sprites
        Iterator i = map.getSprites();
        Bullet bullet2 = null;
        while (i.hasNext()) {
            Sprite sprite = (Sprite)i.next();
            if (sprite instanceof Creature) {
                Creature creature = (Creature)sprite;
                if (creature.getState() == Creature.STATE_DEAD) {
                    i.remove();
                }

                if(creature.getTimer() == 11 && creature.getVelocityX() != 0){
                    boolean direction = player.getX() > creature.getX();
                	bullet2 = (Bullet)resourceManager.getBullet2().clone();
                	bullet2.setX(creature.getX());
                	bullet2.setY(creature.getY());
                	bullet2.setTarget(1);
                	if(direction){
                		bullet2.setVelocityX(bullet2.getSpeed2());
                	}else{
                		bullet2.setVelocityX(-bullet2.getSpeed2());
                	}
                }
                updateCreature(creature, elapsedTime);
            }
            int mapWidth = TileMapRenderer.tilesToPixels(map.getWidth());
            offsetX = width / 2 - Math.round(player.getX()) - TileMapRenderer.getTilesize();
            offsetX = Math.min(offsetX, 0);
            offsetX = Math.max(offsetX, width - mapWidth);
            if (sprite instanceof Bullet){
                Bullet bullet = (Bullet)sprite;
                if(bullet.getState() == Bullet.STATE_DEAD || bullet.getX() <= -offsetX || bullet.getX() >= -offsetX + width){
                	i.remove();
                }else{
                    updateBullet(bullet, elapsedTime);
                }
            }
            // normal update
            sprite.update(elapsedTime);
        }
        if(bullet2 != null){
        	map.addSprite(bullet2);
        }
    }


    /**
        Updates the creature, applying gravity for creatures that
        aren't flying, and checks collisions.
    */
    private void updateCreature(Creature creature,
        long elapsedTime)
    {

        // apply gravity
        if (!creature.isFlying()) {
            creature.setVelocityY(creature.getVelocityY() +
                GRAVITY * elapsedTime);
        }

        // change x
        float dx = creature.getVelocityX();
        float oldX = creature.getX();
        float newX = oldX + dx * elapsedTime;
        Point tile =
            getTileCollision(creature, newX, creature.getY());
        if (tile == null) {
            creature.setX(newX);
        }
        else {
            // line up with the tile boundary
            if (dx > 0) {
                creature.setX(
                    TileMapRenderer.tilesToPixels(tile.x) -
                    creature.getWidth());
            }
            else if (dx < 0) {
                creature.setX(
                    TileMapRenderer.tilesToPixels(tile.x + 1));
            }
            creature.collideHorizontal();
        }
        if (creature instanceof Player) {
            checkPlayerCollision((Player)creature, false);
        }else if( creature.getX() >= -offsetX && creature.getX() < -offsetX + width){
        	if(creature.getFstate() == 0){
        		creature.setFstate(1);
        		creature.setTimer(12);
        	}else if(creature.getFstate() == 4){
        		if(creature.canMove()){
        			creature.setTimer(0);
        			creature.setFstate(0);
        		}else{
        			creature.setFstate(3);
        			creature.setTimer(30);
        		}
        	}
        }else if(creature.getX() < -offsetX || creature.getX() > -offsetX + width){
        	System.out.println("Out of screen");
        	creature.setFstate(4);
        	creature.setTimer(0);
        	creature.resetMove();
        }

        // change y
        float dy = creature.getVelocityY();
        float oldY = creature.getY();
        float newY = oldY + dy * elapsedTime;
        tile = getTileCollision(creature, creature.getX(), newY);
        if (tile == null) {
            creature.setY(newY);
        }
        else {
            // line up with the tile boundary
            if (dy > 0) {
                creature.setY(
                    TileMapRenderer.tilesToPixels(tile.y) -
                    creature.getHeight());
            }
            else if (dy < 0) {
                creature.setY(
                    TileMapRenderer.tilesToPixels(tile.y + 1));
            }
            creature.collideVertical();
        }
        if (creature instanceof Player) {
            boolean canKill = (oldY < creature.getY());
            checkPlayerCollision((Player)creature, canKill);
        }

    }
    private void updateBullet(Bullet bullet, long elapsedtime){
        //Change x
        float dx = bullet.getVelocityX();
        float oldX = bullet.getX();
        float newX = oldX + dx * elapsedtime;
        bullet.setX(newX);
        if(bullet.getTarget() == 0){
        	Sprite collidesprite = getSpriteCollision(bullet);
        	if (collidesprite instanceof Creature){
        		Creature badguy = (Creature) collidesprite;
        		soundManager.play(boopSound);
        		badguy.setState(Creature.STATE_DYING);
        		bullet.setState(Bullet.STATE_DEAD);
        	}
        }
        
    }

    /**
        Checks for Player collision with other Sprites. If
        canKill is true, collisions with Creatures will kill
        them.
    */
    public void checkPlayerCollision(Player player,
        boolean canKill)
    {
        if (!player.isAlive()) {
            return;
        }

        // check for player collision with other sprites
        Sprite collisionSprite = getSpriteCollision(player);
        if (collisionSprite instanceof PowerUp) {
            acquirePowerUp((PowerUp)collisionSprite);
        }
        else if (collisionSprite instanceof Creature) {
            Creature badguy = (Creature)collisionSprite;
            if (canKill) {
                // kill the badguy and make player bounce
                soundManager.play(boopSound);
                badguy.setState(Creature.STATE_DYING);
                player.setY(badguy.getY() - player.getHeight());
                player.jump(true);
            }
            else {
                // player dies!
                player.setState(Creature.STATE_DYING);
            }
        }else if(collisionSprite instanceof Bullet){
        	Bullet bullet = (Bullet) collisionSprite;
        	if(bullet.getTarget() == 1){
        		player.setState(Creature.STATE_DYING);
        		bullet.setState(Bullet.STATE_DEAD);
        	}
        }
    }


    /**
        Gives the player the speicifed power up and removes it
        from the map.
    */
    public void acquirePowerUp(PowerUp powerUp) {
        // remove it from the map
        map.removeSprite(powerUp);

        if (powerUp instanceof PowerUp.Star) {
            // do something here, like give the player points
            soundManager.play(prizeSound);
        }
        else if (powerUp instanceof PowerUp.Music) {
            // change the music
            soundManager.play(prizeSound);
            toggleDrumPlayback();
        }
        else if (powerUp instanceof PowerUp.Goal) {
            // advance to next map
            soundManager.play(prizeSound,
                new EchoFilter(2000, .7f), false);
            map = resourceManager.loadNextMap();
        }
    }

}
