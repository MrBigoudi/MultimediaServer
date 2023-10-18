import java.awt.event.*;

public class CommandButton extends ButtonAction{

    /**
     * The command type
     */
    Command _Command;


    /**
     * A basic constructor
     * @param name The button's name
     * @param window The window to attach the button to
     * @param command The command type
     */
    CommandButton(String name, RemoteControl window, Command command){
        super(name, window);
        _Command = command;
    }

    @Override
    public void actionPerformed(ActionEvent arg0) {
        _Window.sendCommand(_Command, "Film");
    }
    
}