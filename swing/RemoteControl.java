import java.awt.*;
import javax.swing.*;

/**
 * The class representing the remote controls
 */
public class RemoteControl extends JFrame{

    /**
     * The help button
     */
    ButtonAction _ButtonHelp = null;

    /**
     * The save button
     */
    ButtonAction _ButtonSave = null;

    /**
     * The connect button
     */
    ButtonAction _ButtonConnect = null;

    /**
     * The play button
     */
    ButtonAction _ButtonPlay = null;

    /**
     * The search button
     */
    ButtonAction _ButtonSearch = null;

    /**
     * The get database button
     */
    ButtonAction _ButtonGetDB = null;

    /**
     * The quit button
     */
    JButton _ButtonQuit = null;

    /**
     * The text area
     */
    JTextArea _TextZone = null;

    /**
     * The client linked to this control
     */
    Client _Client = null;

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
        _ButtonHelp    = new HelpButton("Help", this);
        _ButtonConnect = new ConnectButton("Connect", this);
        _ButtonPlay    = new CommandButton("Play", this, Command.PLAY);
        _ButtonSearch  = new CommandButton("Search", this, Command.SEARCH);
        _ButtonGetDB   = new CommandButton("GetDB", this, Command.GETDB);
        _ButtonSave    = new CommandButton("Save", this, Command.SAVEDB);
        _ButtonQuit    = new JButton("Quit");
        // add the buttons
        panel.add(new JButton(_ButtonPlay));
        panel.add(new JButton(_ButtonSearch));
        panel.add(new JButton(_ButtonGetDB));
        panel.add(_ButtonQuit);
        // add the actions
        _ButtonQuit.addActionListener(e -> quit());

        // add the panel to the main layout
        add(panel, BorderLayout.SOUTH);
    }

    /**
     * Set a text to the text zone
     * @param text The text to send
     */
    public void setText(String text){
        _TextZone.setText(text);
    }

    /**
     * Create the menu bar
     */
    private void initMenuBar(){
        // init the menu bar
        JMenuBar menuBar = new JMenuBar();
        JMenu menu = new JMenu("Menu");
        menu.add(new JMenuItem(_ButtonHelp));
        menu.add(new JMenuItem(_ButtonConnect));
        menu.add(new JMenuItem(_ButtonSave));
        menuBar.add(menu);
        setJMenuBar(menuBar);
        // init the toolbar
        JToolBar toolBar = new JToolBar();
        toolBar.add(_ButtonHelp);
        toolBar.add(_ButtonConnect);
        toolBar.add(_ButtonSave);
        add(toolBar, BorderLayout.NORTH);
    }

    /**
     * Exit the program
     */
    private void quit(){
        System.exit(0);
    }

    /**
     * Connect a client
     */
    public void connect(){
        String host = Client.DEFAULT_HOST;
        int port = Client.DEFAULT_PORT;
        _Client = Client.connect(host, port);
        setText("Client connected to "+host+":"+port);
    }

    /**
     * Get the command name
     * @param command
     * @param name The argument of the command
     * @return The command as a string
     */
    private String getCommand(Command command, String name){
        switch(command){
            case QUIT:
                return "QUIT";
            case PLAY:
                return "PLAY " + name;
            case SEARCH:
                return "SEARCH " + name;
            case GETDB:
                return "GETDB";
            case SAVEDB:
                return "SAVEDB";
        }
        return "";
    }

    /**
     * Send a command to the client
     * @param command The command type
     * @param name The argument of the command
     */
    public void sendCommand(Command command, String name){
        if(_Client == null){
            setText("Client must be connected before sending a command!");
            return;
        }
        if(command == Command.QUIT){
            quit();
        }
        String request = getCommand(command, name);
        String response = _Client.send(request);
        setText("\n\nResponse: " + response + "\n\n");
    }
}