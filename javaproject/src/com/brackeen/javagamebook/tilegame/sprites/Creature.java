package com.brackeen.javagamebook.tilegame.sprites;

import java.lang.reflect.Constructor;
import com.brackeen.javagamebook.graphics.*;

/**
    A Creature is a Sprite that is affected by gravity and can
    die. It has four Animations: moving left, moving right,
    dying on the left, and dying on the right.
*/
public abstract class Creature extends Sprite {

    /**
        Amount of time to go from STATE_DYING to STATE_DEAD.
    */
    private static final int DIE_TIME = 1000;

    public static final int STATE_NORMAL = 0;
    public static final int STATE_DYING = 1;
    public static final int STATE_DEAD = 2;
    public static final int FSTATE_IDLE = 0;
    public static final int FSTATE_FIRE = 1;
    public static final int FSTATE_COMBO = 2;
    public static final int FSTATE_WAIT = 3;
    public static final int FSTATE_SHOOTEN = 4;
    public static int firerate = 8;

    private Animation left;
    private Animation right;
    private Animation deadLeft;
    private Animation deadRight;
    private int state;
    private int firestate;
    private int timer;
    private long stateTime;
    private boolean direction = true;
    private int move = 0;
    /**
        Creates a new Creature with the specified Animations.
    */
    public Creature(Animation left, Animation right,
        Animation deadLeft, Animation deadRight)
    {
        super(right);
        this.left = left;
        this.right = right;
        this.deadLeft = deadLeft;
        this.deadRight = deadRight;
        state = STATE_NORMAL;
        firestate = FSTATE_WAIT;
    }


    public Object clone() {
        // use reflection to create the correct subclass
        Constructor constructor = getClass().getConstructors()[0];
        try {
            return constructor.newInstance(new Object[] {
                (Animation)left.clone(),
                (Animation)right.clone(),
                (Animation)deadLeft.clone(),
                (Animation)deadRight.clone()
            });
        }
        catch (Exception ex) {
            // should never happen
            ex.printStackTrace();
            return null;
        }
    }


    /**
        Gets the maximum speed of this Creature.
    */
    public float getMaxSpeed() {
        return 0;
    }


    /**
        Wakes up the creature when the Creature first appears
        on screen. Normally, the creature starts moving left.
    */
    public void wakeUp() {
        if (getState() == STATE_NORMAL && getVelocityX() == 0) {
            setVelocityX(-getMaxSpeed());
        }
    }


    /**
        Gets the state of this Creature. The state is either
        STATE_NORMAL, STATE_DYING, or STATE_DEAD.
    */
    public int getState() {
        return state;
    }


    /**
        Sets the state of this Creature to STATE_NORMAL,
        STATE_DYING, or STATE_DEAD.
    */
    public void setState(int state) {
        if (this.state != state) {
            this.state = state;
            stateTime = 0;
            if (state == STATE_DYING) {
                setVelocityX(0);
                setVelocityY(0);
            }
        }
    }


    /**
        Checks if this creature is alive.
    */
    public boolean isAlive() {
        return (state == STATE_NORMAL);
    }


    /**
        Checks if this creature is flying.
    */
    public boolean isFlying() {
        return false;
    }


    /**
        Called before update() if the creature collided with a
        tile horizontally.
    */
    public void collideHorizontal() {
        setVelocityX(-getVelocityX());
    }


    /**
        Called before update() if the creature collided with a
        tile vertically.
    */
    public void collideVertical() {
        setVelocityY(0);
    }
    public boolean getDirection(){
    	return direction;
    }
    public int getFstate(){
    	return firestate;
    }
    public int getTimer(){
    	return timer;
    }
    public void setTimer(int timer){
    	this.timer = timer;
    }
    public void setFstate(int fstate){
    	firestate = fstate;
    }
    public int getFirerate(){
    	return firerate;
    }
    public void resetMove(){
    	move = 2;
    }
    public void setMove(){
    	move -= 1;
    }
    public boolean canMove(){
    	return move == 0;
    }
    /**
        Updates the animaton for this creature.
    */
    public void update(long elapsedTime) {
        // select the correct Animation
        Animation newAnim = anim;
        if (getVelocityX() < 0) {
            newAnim = left;
            direction = false;
        }
        else if (getVelocityX() > 0) {
            newAnim = right;
            direction = true;
        }
        if (state == STATE_DYING && newAnim == left) {
            newAnim = deadLeft;
        }
        else if (state == STATE_DYING && newAnim == right) {
            newAnim = deadRight;
        }
        if(firestate == FSTATE_FIRE){
        	if(timer == 0){
        		firestate = FSTATE_IDLE;
        	}else{
        		timer -= 1;
        	}
        }else if(firestate == FSTATE_COMBO){
    		if(timer == 0){
    			firestate = FSTATE_WAIT;
    			timer = 200;
    		}else{
    			timer -= 1;
    		}
    	}else if(firestate == FSTATE_WAIT){
    		System.out.println("WAIT"+timer);
    		if(timer == 0){
    			firestate = FSTATE_IDLE;
    		}else{
    			timer -= 1;
    		}
    	}
        // update the Animation
        if (anim != newAnim) {
            anim = newAnim;
            anim.start();
        }
        else {
            anim.update(elapsedTime);
        }

        // update to "dead" state
        stateTime += elapsedTime;
        if (state == STATE_DYING && stateTime >= DIE_TIME) {
            setState(STATE_DEAD);
        }
    }

}
