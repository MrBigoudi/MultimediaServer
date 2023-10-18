import java.awt.*;
import javax.swing.*;

/**
 * The class representing the remote controls
 */
public class RemoteControl extends JFrame{

    /**
     * The first button
     */
    ButtonAction _Button1;

    /**
     * The second button
     */
    ButtonAction _Button2;

    /**
     * The quit button
     */
    JButton _QuitButton;

    /**
     * The text area
     */
    JTextArea _TextZone;

    /**
     * Set the class version
     */
    private static final long serialVersionUID = 1L;

    /**
     * A basic consructor
     */
    public RemoteControl(){
        initButtons();
        initTextZone();
        initMenuBar();
        setUP("RemoteControl");        
    }

    /**
     * Set up the main window
     * @param title The window's title
     */
    private void setUP(String title){
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        setTitle(title);
        pack();
        setVisible(true);
    }

    /**
     * Create the text zone
     */
    private void initTextZone(){
        _TextZone = new JTextArea(100, 80);
        JScrollPane pane = new JScrollPane(_TextZone);
        getContentPane().add(pane, BorderLayout.CENTER);
    }

    /**
     * Create the buttons and add their listeners
     */
    private void initButtons(){
        JPanel panel = new JPanel();
        // create the buttons
        _Button1 = new ButtonAction("Button1", this);
        _Button2 = new ButtonAction("Button2", this);
        _QuitButton = new JButton("Quit");
        // add the buttons
        panel.add(new JButton(_Button1));
        panel.add(new JButton(_Button1));
        panel.add(_QuitButton);
        // add the actions
        _QuitButton.addActionListener(e -> quit());

        // add the panel to the main layout
        add(panel, BorderLayout.SOUTH);
    }

    /**
     * Add a line to the text zone
     */
    public void addLine(){
        _TextZone.append("\n");
    }

    /**
     * Create the menu bar
     */
    private void initMenuBar(){
        // init the menu bar
        JMenuBar menuBar = new JMenuBar();
        JMenu menu = new JMenu("Menu");
        menu.add(new JMenuItem(_Button1));
        menu.add(new JMenuItem(_Button2));
        menuBar.add(menu);
        setJMenuBar(menuBar);
        // init the toolbar
        JToolBar toolBar = new JToolBar();
        toolBar.add(_Button1);
        toolBar.add(_Button2);
        add(toolBar, BorderLayout.NORTH);
    }

    /**
     * Exit the program
     */
    private void quit(){
        System.exit(0);
    }

    /**
     * Entry point of the program
     */
    public static void main(String argv[]){
        new RemoteControl();
    }

}