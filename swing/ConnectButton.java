import java.awt.event.*;

public class ConnectButton extends ButtonAction{
    /**
     * A basic constructor
     * @param name The button's name
     * @param window The window to attach the button to
     */
    ConnectButton(String name, RemoteControl window){
        super(name, window);
    }

    @Override
    public void actionPerformed(ActionEvent arg0) {
        _Window.connect();
    }
    
}