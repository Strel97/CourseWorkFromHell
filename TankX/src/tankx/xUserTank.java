package tankx;
import java.awt.image.*;
import java.awt.*;
import java.awt.geom.AffineTransform;
import java.awt.event.*;
import javax.sound.sampled.Clip;

/**
 * <p>Title: ����-�</p>
 *
 * <p>Description: 2D ����</p>
 *
 * <p>Copyright: Copyright (c) 2014 ��������� �������</p>
 *
 * <p>Company: ��������� �������</p>
 *
 * @author ��������� �������
 * @version 1.0
 */

//�������� ������
final class bullet {
    private final static int BUFSIZE = 32;
    private short[] x = null;
    private short[] y = null;
    private char[] dx = null;
    private char[] dy = null;
    private int   cnt = 0;

    public bullet(){
        x   = new short[bullet.BUFSIZE];
        y   = new short[bullet.BUFSIZE];
        dx  = new char[bullet.BUFSIZE];
        dy  = new char[bullet.BUFSIZE];
        cnt = 0;
    }

    public void add(int px, int py, int pdx, int pdy){
        if(cnt < bullet.BUFSIZE){
            x[cnt]  = (short)px;
            y[cnt]  = (short)py;
            dx[cnt] = (char)pdx;
            dy[cnt] = (char)pdy;
            ++cnt;
        }
    }

    public void remove(int index){
        if(index < cnt){
            --cnt;
            for(int i = index; i < cnt; ++i){
                x[i]  = x[i + 1];
                y[i]  = y[i + 1];
                dx[i] = dx[i + 1];
                dy[i] = dy[i + 1];
            }
        }
    }

    public void reset(){
        cnt = 0;
    }

    public int at_x(int i){
        return (int)x[i];
    }

    public int at_y(int i){
        return (int)y[i];
    }

    public void move_all(){
        for(int i = 0; i < cnt; ++i){
            x[i] += (short)dx[i];
            y[i] += (short)dy[i];
        }
    }

    public int count() {
        return cnt;
    }
}



//����-������������
public class xUserTank {
    private BufferedImage  itank;
    private BufferedImage  ishot;
    private bullet         shots;

    private int     x, y;
    private long    delay_mt;
    private int     key_ctrl;
    private double  angle;
    private int     offset;
    private int     speedX, speedY;
    private int     look;
    private int     life;
    private Clip    sfire, stank;

    public final static long DELAY      = 10L;
    public final static int  LOOK_LEFT  = 0;
    public final static int  LOOK_RIGHT = 1;
    public final static int  LOOK_UP    = 2;
    public final static int  LOOK_DOWN  = 3;

    public xUserTank(){
        itank    = null;
        ishot    = null;
        x        = 0;
        y        = 0;
        delay_mt = 0L;
        key_ctrl = 0;
        angle    = 0.0d;
        offset   = 0;
        speedX   = speedY = 0;
        look     = xUserTank.LOOK_UP;
        life     = 0;
        sfire    = null;
        stank    = null;
        shots    = new bullet();
        this.Create();
    }

    //22x38  38x22
    public boolean Create(){
        try {
            itank  = xUtil.ToClip32Bits(this.getClass().getResource("image/tank.jpg"));
            ishot  = xUtil.ToClip32Bits(this.getClass().getResource("image/shot.jpg"));
            sfire  = xUtil.LoadSound(this.getClass().getResource("image/fire.wav"));
            stank  = xUtil.LoadSound(this.getClass().getResource("image/tank.wav"));

            offset = itank.getWidth() / 2;
        } catch(Exception e){
            e.printStackTrace();
            return false;
        }
        return true;
    }


    public void Init(int px, int py) {
        x        = px;
        y        = py;
        life     = 10;
        delay_mt = 0L;
        key_ctrl = 0;
        angle    = 0.0d;
        speedX   = speedY = 0;
        look     = xUserTank.LOOK_UP;
        shots.reset();
        this.Stop();
    }


    public void Stop(){
        sfire.stop();
        stank.stop();
    }


    public void Draw(Graphics2D dc, xField field, long time){
        boolean isdel;
        int ix, iy;

        for(int i = 0; i < shots.count(); ++i){
            ix    = shots.at_x(i);
            iy    = shots.at_y(i);
            isdel = (ix < 0 || iy < 0 || ix >= 640 || iy >= 480);

            if(! isdel){
                switch(field.Offset(ix / xField.CELL_SIZE, iy / xField.CELL_SIZE)) {
                case xField.OPEN_PATH:
                case xField.WOOD_PATH:
                    break;
                case xField.BASE_PATH:
                case xField.BRICK_PATH:
                    field.AddBoom(ix, iy, 1, false);
                    isdel = true;
                    break;
                default:
                    isdel = true;
                    break;
                }
            }

            if(isdel){
                shots.remove(i);
                --i;
                continue;
            }
            dc.drawImage(ishot, ix, iy, null);
        }

        AffineTransform affmat = dc.getTransform();
        affmat.rotate(angle, x + offset, y + offset);
        dc.setTransform(affmat);
        dc.drawImage(itank, x, y, null);

        affmat.setToIdentity();
        dc.setTransform(affmat);

        if((time - delay_mt) > xUserTank.DELAY){
            delay_mt = time;
            if(this.test_collision(key_ctrl, field)){
                x += speedX;
                y += speedY;
            }
            shots.move_all();
        }
    }


    public void KeyPress(int key, xField field){
        int dx, dy;
        if(key == KeyEvent.VK_SPACE) {

            dx = dy = 0;
            switch(look){
            case xUserTank.LOOK_DOWN:
                dy = 3;
                break;
            case xUserTank.LOOK_UP:
                dy = -3;
                break;
            case xUserTank.LOOK_LEFT:
                dx = -3;
                break;
            case xUserTank.LOOK_RIGHT:
                dx = 3;
                break;
            }
            shots.add(x + offset - ishot.getWidth()/2, y + offset - ishot.getHeight()/2, dx, dy);

            if (! sfire.isRunning()) {
                sfire.setFramePosition(0);
                sfire.start();
            }

        } else {

            switch(key){
            case KeyEvent.VK_A:
            case KeyEvent.VK_LEFT:
                speedX = -1;
                angle  = -Math.PI * 0.5d;
                look   = xUserTank.LOOK_LEFT;
                break;
            case KeyEvent.VK_D:
            case KeyEvent.VK_RIGHT:
                speedX = 1;
                angle  = Math.PI * 0.5d;
                look   = xUserTank.LOOK_RIGHT;
                break;
            case KeyEvent.VK_W:
            case KeyEvent.VK_UP:
                speedY = -1;
                angle  = 0.0d;
                look   = xUserTank.LOOK_UP;
                break;
            case KeyEvent.VK_S:
            case KeyEvent.VK_DOWN:
                speedY = 1;
                angle  = Math.PI;
                look   = xUserTank.LOOK_DOWN;
                break;
            }

            if(this.test_collision(key, field)){
                key_ctrl = key;

                if(! stank.isRunning())
                    stank.loop(Clip.LOOP_CONTINUOUSLY);

            } else {
                stank.stop();
                key_ctrl = 0;
            }
        }
    }


    public void KeyUp(int key){
        if(key != KeyEvent.VK_SPACE){
            stank.stop();
            key_ctrl = speedX = speedY = 0;
            this.Reset();
        }
    }


    public int getX(){
        return x;
    }

    public int getY() {
        return y;
    }

    public int getSize(){
        return itank.getWidth();
    }

    public int getLife(){
        return life;
    }

    public int decLife(){
        return --life;
    }

    public bullet getBullets(){
        return shots;
    }

    //********************************************************************************************************************

     private boolean test_collision(int key, xField field){
         boolean iscl;
         int offx, offy;

         switch (key) {
         case KeyEvent.VK_A:
         case KeyEvent.VK_LEFT:

             offx = (x - 1) / xField.CELL_SIZE;
             iscl = (x - 1) < 0;
             if (iscl || field.IsClose(offx, y / xField.CELL_SIZE) ||
                 field.IsClose(offx, (y + itank.getHeight()) / xField.CELL_SIZE)) {
                 this.Reset();
                 return false;
             }

             break;
         case KeyEvent.VK_D:
         case KeyEvent.VK_RIGHT:

             offx = (x + itank.getWidth() + 1) / xField.CELL_SIZE;
             iscl = (x + itank.getWidth() + 1) >= 640;
             if (iscl || field.IsClose(offx, y / xField.CELL_SIZE) ||
                 field.IsClose(offx, (y + itank.getHeight()) / xField.CELL_SIZE)) {
                 this.Reset();
                 return false;
             }

             break;
         case KeyEvent.VK_W:
         case KeyEvent.VK_UP:

             offy = (y - 1) / xField.CELL_SIZE;
             iscl = (y - 1) < 0;
             if (iscl || field.IsClose(x / xField.CELL_SIZE, offy) ||
                 field.IsClose((x + itank.getWidth()) / xField.CELL_SIZE, offy)) {
                 this.Reset();
                 return false;
             }

             break;
         case KeyEvent.VK_S:
         case KeyEvent.VK_DOWN:

             offy = (y + itank.getHeight() + 1) / xField.CELL_SIZE;
             iscl = (y + itank.getHeight() + 1) >= 480;
             if (iscl || field.IsClose(x / xField.CELL_SIZE, offy) ||
                 field.IsClose((x + itank.getWidth()) / xField.CELL_SIZE, offy)) {
                 this.Reset();
                 return false;
             }

             break;
         }
        return true;
    }


    public void Reset(){
       speedX = speedY = key_ctrl = 0;
    }
}