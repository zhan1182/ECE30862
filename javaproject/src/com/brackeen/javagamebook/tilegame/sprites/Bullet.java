package com.brackeen.javagamebook.tilegame.sprites;

import java.lang.reflect.Constructor;
import com.brackeen.javagamebook.graphics.*;
import com.brackeen.javagamebook.graphics.Animation;

public class Bullet extends Sprite{
    
    public static final int STATE_DEAD = 0;
    public static final int STATE_ALIVE = 1;

    private int target = 0;//0 = enermy, 1 = player
    private int direction = 0;//0 = l, 1 = r
    private int state = STATE_ALIVE;

    public Bullet(Animation anim){
        super(anim);
    }
    public Object clone() {
        // use reflection to create the correct subclass
        Constructor constructor = getClass().getConstructors()[0];
        try {
            return constructor.newInstance(new Object[] {
                (Animation)anim.clone()
            });
        }
        catch (Exception ex) {
            // should never happen
            ex.printStackTrace();
            return null;
        }
    }
    public int getTarget(){
        return target;
    }
    public int getDirection(){
        return direction;
    }
    public void setTarget(int t){
        this.target = t;
    }
    public void setDirection(int d){
        this.direction = d;
    }
    public void collideHorizontal() {
        setVelocityX(0);
    }
    public float getSpeed1(){
        return 0.5f;
    }
    public float getSpeed2(){
        return 0.2f;
    }
    public void setState(int state){
        this.state = state;
    }
    public int getState(){
        return state;
    }
}
    
    

    
