package tankx;
import java.awt.image.*;
import java.awt.*;
import java.io.*;
import java.util.*;
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


// �����
final class boom {
    private int  x, y, start_row, start_col;
    private long time;

    public final static int CADR_COLS = 5;
    public final static int CADR_ROWS = 2;

    public boom(int px, int py, int row){
        x         = px;
        y         = py;
        start_row = row;
        start_col = 0;
        time      = 0L;
    }

    public boolean update_frame(long msec){
        if((msec - time) > 92L){
            time = msec;
            if(++start_col >= boom.CADR_COLS){
                start_col = 0;
                if(++start_row >= boom.CADR_ROWS)
                    return true;
            }
        }
        return false;
    }

    public int getX(){
        return x;
    }

    public int getY(){
        return y;
    }

    public int getRow(){
        return start_row;
    }

    public int getCol(){
        return start_col;
    }
}



// �����-������������� ���������
final class xAlien {
    private Vector<Integer> pos = null;
    private short   posx, posy;
    private short   info;
    private int     index;
    private long    tmove;
    private float   finc, fspeed;
    private boolean irun;

    public final static short ALIEN_A = 0;
    public final static short ALIEN_B = 1;
    public final static short ALIEN_C = 2;

    public xAlien(int x, int y, float speed, short type, short life){
        pos  = new Vector<Integer>();
        Initialize(x, y, speed, type, life);
    }

    public void Initialize(int x, int y, float speed, short type, short life){
        posx   = (short)x;
        posy   = (short)y;
        fspeed = speed;
        info   = (short)((type << 8) | life);
        index  = 0;
        tmove  = 0L;
        finc   = 0.0f;
        irun   = true;
    }

    public void run(){
        irun  = true;
        index = 0;
    }

    public int decLife(){
        int life = getLife() - 1;
        if(life <= 0)
            info &= 0xFF00;
        else
            info  = (short)((info & 0xFF00) | (short)life);
        return life;
    }

    public Vector<Integer> getArray(){
        return pos;
    }

    public int getX() {
        return (int)posx;
    }

    public int getY() {
        return (int)posy;
    }

    public int getLife(){
        return (int)(info & 0xFF);
    }

    public int getType(){
        return (int)(info >> 8);
    }

    public boolean isRun(){
        return irun;
    }

    public void Destroy(){
        if(pos != null){
            pos.clear();
            pos = null;
        }
    }

    public boolean UpdateFrame(long msec){
        int px1, py1, px2, py2;

        if(! irun)
            return false;

        if((msec - tmove) > 10L){
            tmove = msec;

            if((index + 1) < pos.size()){
                px1  = (int) (pos.get(index) >> 16);
                py1  = (int) (pos.get(index) & 0xFFFF);
                px2  = (int) (pos.get(index + 1) >> 16);
                py2  = (int) (pos.get(index + 1) & 0xFFFF);
                posx = (short) ((float) (px2 - px1) * finc + (float) px1);
                posy = (short) ((float) (py2 - py1) * finc + (float) py1);
            }

            finc += fspeed;
            if(finc >= 1.0f){
                finc = 0.0f;
                if (++index >= pos.size()) {
                    irun  = false;
                    index = 0;
                    return true;
                }
            }
        }
        return false;
    }
};




//������� ����
public class xField {
    private BufferedImage    dblbuf;
    private BufferedImage    icopy;
    private BufferedImage    ialien;
    private Graphics2D       dcbuf;
    private Graphics2D       dcboom;
    private BufferedImage    tiles;
    private BufferedImage    iboom;
    private char[]           field;
    private int              fwidth;
    private int              fheight;
    private int              dimboom;
    private Clip             sboom, scrash, sbron;

    private Vector<String>     levels;
    private LinkedList<boom>   booms;
    private LinkedList<xAlien> aliens;



    public final static char OPEN_PATH   = '0';
    public final static char WOOD_PATH   = '1';
    public final static char BRICK_PATH  = '2';
    public final static char BLOCK_PATH  = '3';
    public final static char BASE_PATH   = '4';
    public final static char ALIEN_BEGIN = '5';
    public final static char ALIEN_END   = '7';
    public final static char USER_PATH   = '8';
    public final static int  CELL_SIZE   = 32;

    public xField() {
        dblbuf  = null;
        icopy   = null;
        ialien  = null;
        dcbuf   = null;
        dcboom  = null;
        tiles   = null;
        field   = null;
        fwidth  = fheight = 0;
        dimboom = 0;
        sboom   = null;
        scrash  = null;
        sbron   = null;
        levels  = null;
        booms   = null;
        aliens  = null;
    }

    public boolean Create(int width, int height) {
        int        ch;
        String     buf = "";
        InputStream fp = null;
        dblbuf = new BufferedImage(width, height, BufferedImage.TYPE_INT_ARGB);
        icopy  = new BufferedImage(width, height, BufferedImage.TYPE_INT_ARGB);
        dcbuf  = dblbuf.createGraphics();
        dcboom = icopy.createGraphics();

        fwidth  = width  / xField.CELL_SIZE;
        fheight = height / xField.CELL_SIZE;
        field   = new char[fwidth * fheight];
        booms   = new LinkedList<boom>();
        aliens  = new LinkedList<xAlien>();
        levels  = new Vector<String>();

        sboom   = xUtil.LoadSound(this.getClass().getResource("image/boom.wav"));
        scrash  = xUtil.LoadSound(this.getClass().getResource("image/crash.wav"));
        sbron   = xUtil.LoadSound(this.getClass().getResource("image/bron.wav"));

        try {
            ialien = xUtil.ToClip32Bits(this.getClass().getResource("image/aliens.jpg"));
            iboom  = xUtil.ToClip32Bits(this.getClass().getResource("image/boom.jpg"));
            tiles  = xUtil.ToClip32Bits(this.getClass().getResource("image/tiles.jpg"), 0xFFFF00FF);
            fp     = this.getClass().getResource("image/levels.au").openStream();
            buf    = "";
            do {
                ch = fp.read();
                if(ch == '+') {
                    levels.add(buf);
                    buf = "";
                } else if(Character.isDigit(ch))
                    buf += (char)ch;
            } while(ch != -1);

            fp.close();
            fp = null;
        } catch(IOException e){
           e.printStackTrace();
           return false;
        }

        dimboom = ((iboom.getWidth(null) / boom.CADR_COLS) << 16) | (iboom.getHeight(null) / boom.CADR_ROWS);
        return true;
    }


    public boolean StartLevel(int level, xUserTank user){
        float speed = 0.0f;
        short type  = 0, life = 0;

        for(int i = 0; i < aliens.size(); ++i){
            aliens.get(i).Destroy();
            aliens.set(i, null);
        }
        aliens.clear();
        booms.clear();

        if(level >= levels.size())
            return false;

        String str = levels.get(level);
        for(int i = 0; i < str.length(); ++i)
            field[i] = str.charAt(i);

        int row;
        for(int r = 0; r < fheight; ++r){
            row = r * fwidth;
            for(int c = 0; c < fwidth; ++c){
                if(field[row + c] == xField.USER_PATH) {
                    field[row + c] = xField.OPEN_PATH;
                    user.Init(c * xField.CELL_SIZE, r * xField.CELL_SIZE);
                    r = fheight;
                    break;
                }
            }
        }


        for(int r = 0; r < fheight; ++r){
            row = r * fwidth;
            for(int c = 0; c < fwidth; ++c) {
                if((field[row + c] >= xField.ALIEN_BEGIN) && (field[row + c] <= xField.ALIEN_END)) {
                    switch(field[row + c]){
                    case xField.ALIEN_BEGIN:
                        speed = 0.02f;
                        type  = 0;
                        life  = 3;
                        break;
                    case xField.ALIEN_BEGIN + 1:
                        speed = 0.03f;
                        type  = 1;
                        life  = 4;
                        break;
                    case xField.ALIEN_BEGIN + 2:
                        speed = 0.034f;
                        type  = 2;
                        life  = 2;
                        break;
                    }
                    field[row + c] = xField.OPEN_PATH;

                    aliens.add(new xAlien(c * xField.CELL_SIZE, r * xField.CELL_SIZE, speed, type, life));
                    switch(aliens.getLast().getType()){
                    case xAlien.ALIEN_A:
                        xUtil.FindPathDFS(this, aliens.getLast().getX(), aliens.getLast().getY(), user.getX(), user.getY(), aliens.getLast().getArray());
                        break;
                    case xAlien.ALIEN_B:
                        xUtil.FindPathBFS(this, aliens.getLast().getX(), aliens.getLast().getY(), user.getX(), user.getY(), aliens.getLast().getArray());
                        break;
                    case xAlien.ALIEN_C:
                        xUtil.ShortestWave(this, aliens.getLast().getX(), aliens.getLast().getY(), user.getX(), user.getY(), aliens.getLast().getArray());
                        break;
                    }
                }
            }
        }

        this.update();
        return true;
    }


    public void Stop(){
        sboom.stop();
        scrash.stop();
        sbron.stop();
    }


    public int getCountAliens(){
        return aliens.size();
    }


    public boolean IsOpen(int x, int y){
        if((x >= 0 && x < fwidth) && (y > 0 && y < fheight))
            return (field[y * fwidth + x] <= xField.WOOD_PATH);
        return false;
    }

    public boolean IsClose(int x, int y){
        if((x >= 0 && x < fwidth) && (y > 0 && y < fheight))
            return (field[y*fwidth + x] > xField.WOOD_PATH);
        return false;
    }

    public char Offset(int x, int y){
        return field[y*fwidth + x];
    }


    public void PutChange(int x, int y, char val){
        field[y*fwidth + x] = val;
        x *= xField.CELL_SIZE;
        y *= xField.CELL_SIZE;
        dcboom.drawImage(icopy,  x, y, x + xField.CELL_SIZE, y + xField.CELL_SIZE,
                         0, 0, xField.CELL_SIZE, xField.CELL_SIZE, null);
    }


    public void AddBoom(int x, int y, int begin_row, boolean i_alien) {
        int  cx = dimboom >> 16;
        int  cy = dimboom & 0xFFFF;
        if(! i_alien) {
            x = x / xField.CELL_SIZE * xField.CELL_SIZE;
            y = y / xField.CELL_SIZE * xField.CELL_SIZE;
        }
        boom bl = new boom(x + (xField.CELL_SIZE - cx)/2, y + (xField.CELL_SIZE - cy)/2, begin_row);
        booms.add(bl);

        if(! i_alien) {
            PutChange(x / xField.CELL_SIZE, y / xField.CELL_SIZE, xField.OPEN_PATH);
            if(! sboom.isRunning()){
                sboom.setFramePosition(0);
                sboom.start();
            }
        } else {
            if (! scrash.isRunning()) {
                scrash.setFramePosition(0);
                scrash.start();
            }
        }
    }




    public void Draw(long time, xUserTank user){
        boom bl;
        int row, px, py;

        if(! aliens.isEmpty()){

            xAlien alien;
            for(Iterator<xAlien> it = aliens.listIterator(); it.hasNext(); ){
                alien = it.next();
                dcbuf.drawImage(ialien, alien.getX(), alien.getY(), alien.getX() + xField.CELL_SIZE,
                                alien.getY() + xField.CELL_SIZE, alien.getType() * xField.CELL_SIZE, 0,
                                alien.getType() * xField.CELL_SIZE + xField.CELL_SIZE, xField.CELL_SIZE, null);

                if (alien.UpdateFrame(time)) {
                    switch (alien.getType()) {
                    case xAlien.ALIEN_A:
                        xUtil.FindPathDFS(this, alien.getX(), alien.getY(), user.getX(), user.getY(), alien.getArray());
                        break;
                    case xAlien.ALIEN_B:
                        xUtil.FindPathBFS(this, alien.getX(), alien.getY(), user.getX(), user.getY(), alien.getArray());
                        break;
                    case xAlien.ALIEN_C:
                        xUtil.ShortestWave(this, alien.getX(), alien.getY(), user.getX(), user.getY(), alien.getArray());
                        break;
                    }
                    alien.run();
                }
            }

        } else {
            // ������� ������� �� ����� �������
        }


        // ������� �����
        if(! booms.isEmpty()) {
            px = dimboom >> 16;
            py = dimboom & 0xFFFF;
            Iterator<boom> prv, it = booms.iterator();
            while(it.hasNext()){
                prv = it;
                bl  = it.next();
                if(bl.update_frame(time)){
                    prv.remove();
                    break;
                } else {
                    dcbuf.drawImage(iboom, bl.getX(), bl.getY(), bl.getX() + px, bl.getY() + py,
                                    bl.getCol()*px, bl.getRow()*py, bl.getCol()*px+px, bl.getRow()*py+py, null);
                }
            }
        }


        for(int y = 0; y < fheight; ++y){
            row = y*fwidth;
            for(int x = 0; x < fwidth; ++x){
                if(field[row + x] == xField.WOOD_PATH){
                    px = x * xField.CELL_SIZE;
                    py = y * xField.CELL_SIZE;
                    dcbuf.drawImage(tiles,  x * xField.CELL_SIZE, py, px + xField.CELL_SIZE, py + xField.CELL_SIZE,
                                    xField.CELL_SIZE, 0, xField.CELL_SIZE << 1, xField.CELL_SIZE, null);
                }
            }
        }
    }


    //�������� ������������ ����� � ���
    public boolean IsCollision(xUserTank user){
        int res, rad;
        xAlien alien;
        Iterator<xAlien> prv, it = aliens.iterator();
        while(it.hasNext()){
            prv   = it;
            alien = it.next();
            res = (user.getX() - alien.getX())*(user.getX() - alien.getX()) + (user.getY() - alien.getY())*(user.getY() - alien.getY());
            rad = (user.getSize() + xField.CELL_SIZE-31) * (user.getSize() + xField.CELL_SIZE-31);
            if(res < rad){
                user.decLife();
                if(alien.decLife() == 0){
                    AddBoom(alien.getX(), alien.getY(), 0, true);
                    alien.Destroy();
                    alien = null;
                    prv.remove();
                }
                return true;
            }
        }
        return false;
    }


    //�������� ������������ ����
    public boolean IsBulletsCollision(xUserTank user) {
        int ix, iy;
        xAlien alien;
        Iterator<xAlien> prv, it;
        bullet bls = user.getBullets();

        for (int i = 0; i < bls.count(); ++i) {
            ix = bls.at_x(i);
            iy = bls.at_y(i);

            for (it = aliens.iterator(); it.hasNext(); ) {
                prv   = it;
                alien = it.next();
                if ((ix > alien.getX() && ix < alien.getX() + xField.CELL_SIZE) &&
                    (iy > alien.getY() && iy < alien.getY() + xField.CELL_SIZE)) {
                    bls.remove(i);
                    if (alien.decLife() == 0){
                        AddBoom(alien.getX(), alien.getY(), 0, true);
                        alien.Destroy();
                        alien = null;
                        prv.remove();
                    } else {
                        if(! sbron.isRunning()){
                            sbron.setFramePosition(0);
                            sbron.start();
                        }
                    }
                    return true;
                }
            }
        }
        return false;
    }


    public Graphics2D GetDC() {
        return dcbuf;
    }

    public BufferedImage Handle() {
        return dblbuf;
    }

    public void Erase() {
        dcbuf.drawImage(icopy, 0, 0, null);
    }

    public int  GetWidth() {
        return fwidth;
    }

    public int GetHeight(){
        return fheight;
    }


    private void update(){
        int px, py, pos, index;
        for(int y = 0; y < fheight; ++y) {
            py = y * xField.CELL_SIZE;
            for(int x = 0; x < fwidth; ++x){
                px    = x * xField.CELL_SIZE;
                index = (int)(field[y*fwidth + x] - '0');
                if(index == 1)
                    --index;
                pos   = index * xField.CELL_SIZE;
                dcboom.drawImage(tiles,  x * xField.CELL_SIZE, py, px + xField.CELL_SIZE, py + xField.CELL_SIZE,
                             pos, 0, pos + xField.CELL_SIZE, xField.CELL_SIZE, null);
            }
        }
    }

}
