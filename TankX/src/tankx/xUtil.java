package tankx;
import java.awt.image.*;
import java.util.*;
import java.io.File;
import javax.sound.sampled.*;


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



public class xUtil {
    public static Queue<Integer> pqs = new LinkedList<Integer>();
    public static Stack<Integer> stk = new Stack<Integer>();
    public static char[] px = null;
    public static char[] py = null;
    public static int[] vis = null;


    // BFS - �������� ������ ���� � ������
    static boolean FindPathBFS(xField field, int start_x, int start_y, int end_x,
                            int end_y, Vector<Integer> path) {

        int inx, cur, x, y;
        boolean isfnd = false;
        int[]   dirs  = {1, 0, 0, 1, -1, 0, 0, -1};

        start_x /= xField.CELL_SIZE;
        start_y /= xField.CELL_SIZE;
        end_x   /= xField.CELL_SIZE;
        end_y   /= xField.CELL_SIZE;

        if(vis == null) {
            px  = new char[field.GetWidth() * field.GetHeight()];
            py  = new char[field.GetWidth() * field.GetHeight()];
            vis = new int[field.GetWidth() * field.GetHeight()];
        }
        for (int i = 0; i < vis.length; ++i)
            vis[i] = Integer.MAX_VALUE;

        pqs.add((start_x << 16) | start_y);
        vis[start_y * field.GetWidth() + start_x] = 0;

        while (! pqs.isEmpty()) {
            cur = pqs.peek();
            pqs.remove();

            x = cur >> 16;
            y = cur & 0xFFFF;
            if ((x == end_x) && (y == end_y)) {
                isfnd = true;
                break;
            }

            for (int i = 0; i < dirs.length; i += 2) {
                int nx = x + dirs[i];
                int ny = y + dirs[i + 1];
                if ((nx < 0) || (ny < 0) || (nx >= field.GetWidth()) ||
                    (ny >= field.GetHeight()))
                    continue;
                if (field.Offset(nx, ny) > xField.WOOD_PATH)
                    continue;

                inx = ny * field.GetWidth() + nx;
                if (vis[inx] > (vis[y * field.GetWidth() + x] + 1)) {
                    px[inx] = (char) x;
                    py[inx] = (char) y;
                    vis[inx] = vis[y * field.GetWidth() + x] + 1;
                    pqs.add((nx << 16) | ny);
                }
            }
        }
        pqs.clear();


        if(isfnd){
            path.clear();
            x = (end_x << 16)   | end_y;
            y = (start_x << 16) | start_y;
            path.add(((end_x * xField.CELL_SIZE) << 16) | (end_y * xField.CELL_SIZE));
            while (x != y) { // �������� ����
                inx = (x & 0xFFFF) * field.GetWidth() + (x >> 16);
                path.add((((int) px[inx] * xField.CELL_SIZE) << 16) | ((int) py[inx] * xField.CELL_SIZE));
                x   = ((int) px[inx] << 16) | (int) py[inx];
            }
        }

        if(! path.isEmpty()){
            int a = 0, b = path.size() - 1;
            while (a < b) { //����������� ����
                inx = path.get(a);
                path.set(a, path.get(b));
                path.set(b, inx);
                ++a;
                --b;
            }
        }
        return isfnd;
    }


    // DFS - �������� ������ ���� � �������
    static boolean FindPathDFS(xField field, int start_x, int start_y, int end_x,
                            int end_y, Vector<Integer> path) {
        int inx, cur, x, y;
        boolean isfnd = false;
        int[]   dirs  = {1, 0, 0, 1, -1, 0, 0, -1};

        start_x /= xField.CELL_SIZE;
        start_y /= xField.CELL_SIZE;
        end_x   /= xField.CELL_SIZE;
        end_y   /= xField.CELL_SIZE;

        if(vis == null) {
            px  = new char[field.GetWidth() * field.GetHeight()];
            py  = new char[field.GetWidth() * field.GetHeight()];
            vis = new int[field.GetWidth() * field.GetHeight()];
        }
        for (int i = 0; i < vis.length; ++i)
            vis[i] = Integer.MAX_VALUE;

        stk.push((start_x << 16) | start_y);
        vis[start_y * field.GetWidth() + start_x] = 0;

        while (! stk.isEmpty()) {
            cur = stk.peek();
            stk.pop();

            x = cur >> 16;
            y = cur & 0xFFFF;
            if ((x == end_x) && (y == end_y)) {
                isfnd = true;
                break;
            }

            for (int i = 0; i < dirs.length; i += 2) {
                int nx = x + dirs[i];
                int ny = y + dirs[i + 1];
                if ((nx < 0) || (ny < 0) || (nx >= field.GetWidth()) ||
                    (ny >= field.GetHeight()))
                    continue;
                if (field.Offset(nx, ny) > xField.WOOD_PATH)
                    continue;

                inx = ny * field.GetWidth() + nx;
                if (vis[inx] > (vis[y * field.GetWidth() + x] + 1)) {
                    px[inx] = (char) x;
                    py[inx] = (char) y;
                    vis[inx] = vis[y * field.GetWidth() + x] + 1;
                    stk.push((nx << 16) | ny);
                }
            }
        }
        stk.clear();


        if(isfnd){
            path.clear();
            x = (end_x << 16)   | end_y;
            y = (start_x << 16) | start_y;
            path.add(((end_x * xField.CELL_SIZE) << 16) | (end_y * xField.CELL_SIZE));
            while (x != y) { // �������� ����
                inx = (x & 0xFFFF) * field.GetWidth() + (x >> 16);
                path.add((((int) px[inx] * xField.CELL_SIZE) << 16) | ((int) py[inx] * xField.CELL_SIZE));
                x   = ((int) px[inx] << 16) | (int) py[inx];
            }
        }

        if(! path.isEmpty()){
            int a = 0, b = path.size() - 1;
            while (a < b) { //����������� ����
                inx = path.get(a);
                path.set(a, path.get(b));
                path.set(b, inx);
                ++a;
                --b;
            }
        }
        return isfnd;
    }



    // �������� �������� ��� ������ ����������� ����
    public static boolean ShortestWave(xField field, int start_x, int start_y, int end_x, int end_y, Vector<Integer> path){
        int     nx, ny, row, cnt = 1;
        boolean ifnd = false;
        int[]   dirs = { 1, 0, 0, 1, -1, 0, 0, -1 };

        if(vis == null){
            vis = new int[field.GetWidth() * field.GetHeight()];
            px  = new char[field.GetWidth() * field.GetHeight()];
            py  = new char[field.GetWidth() * field.GetHeight()];
        }
        for(int r = 0; r < field.GetHeight(); ++r){
            row = r * field.GetWidth();
            for(int c = 0; c < field.GetWidth(); ++c)
                vis[row + c] = (field.Offset(c, r) <= xField.WOOD_PATH) ? 0 : Integer.MAX_VALUE;
        }
        start_x /= xField.CELL_SIZE;
        start_y /= xField.CELL_SIZE;
        end_x   /= xField.CELL_SIZE;
        end_y   /= xField.CELL_SIZE;

        vis[end_y * field.GetWidth() + end_x] = 1;
        vis[start_y * field.GetWidth() + start_x] = 0;

        // ��a���� �������� ��� ��������� ������ �� ����������� �����
        for (boolean loop = true; loop; ++cnt) {
            loop = false;
            for (int r = 0; r < field.GetHeight(); r++) {
                row = r * field.GetWidth();
                for (int c = 0; c < field.GetWidth(); c++) {
                    if (vis[row + c] != cnt)
                        continue;
                    for (int i = 0; i < dirs.length; i += 2) { // �������� � ������ �������
                        nx = c + dirs[i];
                        ny = r + dirs[i + 1];
                        if ((nx < 0) || (ny < 0) || (nx >= field.GetWidth()) || (ny >= field.GetHeight()))
                            continue;

                        if (vis[ny * field.GetWidth() + nx] == 0) { // ���� ���� ���������
                            vis[ny * field.GetWidth() + nx] = cnt + 1;
                            loop = true;
                        }
                    }
                    if ((r == start_y) && (c == start_x))
                        ifnd = true;
                }
            }
        }

        if (ifnd) {
            path.clear();
            int i = start_y;
            int j = start_x;
            while (vis[i * field.GetWidth() + j] > 1) {
                for (int v = 0; v < dirs.length; v += 2) {
                    ny = i + dirs[v];
                    nx = j + dirs[v + 1];
                    if ((nx > -1 && nx < field.GetWidth()) &&
                        (ny > -1 && ny < field.GetHeight())) {
                        if (vis[ny * field.GetWidth() + nx] < vis[i * field.GetWidth() + j]) {
                            i = ny;
                            j = nx;
                            break;
                        }
                    }
                }
                path.add(((j * xField.CELL_SIZE) << 16) | (i*xField.CELL_SIZE));
            }

        } else {
            int a = 0, b = path.size() - 1;
            while (a < b) {
                row = path.get(a);
                path.set(a, path.get(b));
                path.set(b, row);
                ++a;
                --b;
            }
        }
        return ifnd;
    }



    public static BufferedImage ToClip32Bits(java.net.URL url) {
        BufferedImage simg, dimg;
        try {
            simg = javax.imageio.ImageIO.read(url);
            dimg = new BufferedImage(simg.getWidth(), simg.getHeight(), BufferedImage.TYPE_INT_ARGB);
        } catch(Exception e){
            e.printStackTrace();
            simg = dimg = null;
            return null;
        }
        int rgb, color = simg.getRGB(0, 0);
        for(int y = 0; y < simg.getHeight(); ++y){
            for(int x = 0; x < simg.getWidth(); ++x){
                if((rgb = simg.getRGB(x, y)) != color)
                    dimg.setRGB(x, y, 0xFF000000 | rgb);
                else
                    dimg.setRGB(x, y, 0);
            }
        }
        simg = null;
        return dimg;
    }



    public static BufferedImage ToClip32Bits(java.net.URL url, int color_key) {
        BufferedImage simg, dimg;
        try {
            simg = javax.imageio.ImageIO.read(url);
            dimg = new BufferedImage(simg.getWidth(), simg.getHeight(), BufferedImage.TYPE_INT_ARGB);
        } catch(Exception e){
            e.printStackTrace();
            simg = dimg = null;
            return null;
        }
        int rgb;
        for(int y = 0; y < simg.getHeight(); ++y){
            for(int x = 0; x < simg.getWidth(); ++x){
                if((rgb = simg.getRGB(x, y)) != color_key)
                    dimg.setRGB(x, y, 0xFF000000 | rgb);
                else
                    dimg.setRGB(x, y, 0);
            }
        }
        simg = null;
        return dimg;
    }


    // �������� ����� �� ��������
    public static Clip LoadSound(java.net.URL url){
        Clip clip = null;
        AudioFileFormat  fmt = null;
        try {
            fmt  = AudioSystem.getAudioFileFormat(url);
            clip = (Clip)AudioSystem.getLine(new DataLine.Info(Clip.class, fmt.getFormat()));
            clip.open(AudioSystem.getAudioInputStream(url));
        } catch(Exception e){
            e.printStackTrace();
        } finally {
            fmt = null;
        }
        return clip;
    }


    // �������� ����� �� �����
    public static Clip LoadSound(String filename){
        File file = null;
        Clip clip = null;
        AudioFileFormat  fmt = null;
        try {
            file = new File(filename);
            fmt  = AudioSystem.getAudioFileFormat(file);
            clip = (Clip)AudioSystem.getLine(new DataLine.Info(Clip.class, fmt.getFormat()));
            clip.open(AudioSystem.getAudioInputStream(file));
        } catch(Exception e){
            e.printStackTrace();
        } finally {
            fmt  = null;
            file = null;
        }
        return clip;
    }
}