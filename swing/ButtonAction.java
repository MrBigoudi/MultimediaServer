import javax.swing.*;

public abstract class ButtonAction extends AbstractAction {

    /**
     * The main window from which the button is attached to
     */
    RemoteControl _Window;

    /**
     * A basic constructor
     * @param name The button's name
     * @param window The window to attach the button to
     */
    ButtonAction(String name, RemoteControl window){
        super(name);
        _Window = window;
    }
    
}
