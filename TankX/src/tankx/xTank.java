package tankx;

import java.awt.Toolkit;
import javax.swing.SwingUtilities;
import javax.swing.UIManager;
import java.awt.Dimension;

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
public class xTank {
    boolean packFrame = false;

    /**
     * Construct and show the application.
     */
    public xTank() {
        DlgFrame frame = new DlgFrame();
        // Validate frames that have preset sizes
        // Pack frames that have useful preferred size info, e.g. from their layout
        if (packFrame) {
            frame.pack();
        } else {
            frame.validate();
        }

        // Center the window
        Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
        Dimension frameSize = frame.getSize();
        if (frameSize.height > screenSize.height) {
            frameSize.height = screenSize.height;
        }
        if (frameSize.width > screenSize.width) {
            frameSize.width = screenSize.width;
        }
        frame.setLocation((screenSize.width - frameSize.width) / 2,
                          (screenSize.height - frameSize.height) / 2);
        frame.setVisible(true);
    }

    /**
     * Application entry point.
     *
     * @param args String[]
     */
    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            public void run() {
                try {
                    UIManager.setLookAndFeel(UIManager.getLookAndFeel());
                } catch (Exception exception) {
                    exception.printStackTrace();
                }

                new xTank();
            }
        });
    }
}
