//
// Client Java pour communiquer avec le Serveur C++ 
// eric lecolinet - telecom paristech - 2015
//

import java.io.*;
import java.net.*;

public class Client{
    private static final long serialVersionUID = 1L;
    static final String DEFAULT_HOST = "localhost";
    static final int DEFAULT_PORT = 3331;
    private Socket sock;
    private BufferedReader input;
    private BufferedWriter output;

    static final int NB_COMMANDS = 5;
    static final String[] COMMANDS_NAME = {
        "QUIT", 
        "PLAY", 
        "SEARCH", 
        "GETDB", 
        "SAVEDB"
    };
    static final String[] COMMANDS_DESCRIPTION = {
        "Quit the app",
        "Play a media form the data base",
        "Display the properties of a multimedia in the database",
        "Display the entire database",
        "Save the database in the '/cpp/media/db.json' file"
    };

    /**
     * Create a string to explain all the commands
     * @return The message string
     */
    public static String help() {
        StringBuilder helpText = new StringBuilder("\n\nAvailable commands:\n");
    
        for (int i = 0; i < NB_COMMANDS; i++) {
            helpText.append(
                "\tname: ").append(COMMANDS_NAME[i]).append("\n")
                .append("\tdesc: ").append(COMMANDS_DESCRIPTION[i]).append("\n\n");
        }
    
        return helpText.toString();
    }

    /**
     * Connect the client to the server
     * @param host The name of the host
     * @param port The port of the server
     * @return The connected client
     */
    public static Client connect(String host, int port){    
        Client client = null;
    
        try {
            client = new Client(host, port);
        }
        catch (Exception e) {
            System.err.println("Client: Couldn't connect to "+host+":"+port);
            System.exit(1);
        }
    
        System.out.println("Client connected to "+host+":"+port);
        return client;
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  
    ///
    /// Lit une requete depuis le Terminal, envoie cette requete au serveur,
    /// recupere sa reponse et l'affiche sur le Terminal.
    /// Noter que le programme bloque si le serveur ne repond pas.
    ///
    public static void main(String argv[]) {
        new RemoteControl();
        

        // // pour lire depuis la console
        // BufferedReader cin = new BufferedReader(new InputStreamReader(System.in));
    
        // while (true) {
        //     help();
        //     System.out.print("Request: ");
        //     try {
        //         String request = cin.readLine();
        //         if(request.compareTo(COMMANDS_NAME[0]) == 0) return;
        //         String response = client.send(request);
        //         System.out.println("Response: " + response);
        //     }
        //     catch (java.io.IOException e) {
        //         System.err.println("Client: IO error");
        //         return;
        //     }
        // }
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    ///
    /// Initialise la connexion.
    /// Renvoie une exception en cas d'erreur.
    ///
    public Client(String host, int port) throws UnknownHostException, IOException {
        try {
            sock = new java.net.Socket(host, port);
        }
        catch (java.net.UnknownHostException e) {
            System.err.println("Client: Couldn't find host "+host+":"+port);
            throw e;
        }
        catch (java.io.IOException e) {
            System.err.println("Client: Couldn't reach host "+host+":"+port);
            throw e;
        }
    
        try {
            input = new BufferedReader(new InputStreamReader(sock.getInputStream()));
            output = new BufferedWriter(new OutputStreamWriter(sock.getOutputStream()));
        }
        catch (java.io.IOException e) {
            System.err.println("Client: Couldn't open input or output streams");
            throw e;
        }
    }
  
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  
    ///
    /// Envoie une requete au server et retourne sa reponse.
    /// Noter que la methode bloque si le serveur ne repond pas.
    ///
    public String send(String request) {
        // Envoyer la requete au serveur
        try {
            request += "\n";  // ajouter le separateur de lignes
            output.write(request, 0, request.length());
            output.flush();
        }
        catch (java.io.IOException e) {
            return "Client: Couldn't send message: " + e;
        }
    
        // Recuperer le resultat envoye par le serveur
        try {
            return input.readLine();
        }
        catch (java.io.IOException e) {
            return "Client: Couldn't receive message: " + e;
        }
    }
}