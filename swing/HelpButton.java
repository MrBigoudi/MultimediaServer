import java.awt.event.*;

public class HelpButton extends ButtonAction {

    /**
     * A basic constructor
     * @param name The button's name
     * @param window The window to attach the button to
     */
    HelpButton(String name, RemoteControl window){
        super(name, window);
    }

    @Override
    public void actionPerformed(ActionEvent arg0) {
        _Window.setText(Client.help());
    }
    
}
