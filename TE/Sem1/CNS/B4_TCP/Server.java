import java.io.*;
import java.net.*;

public class Server {
    public static void main(String[] args) {
        try {
            ServerSocket serverSocket = new ServerSocket(5000);
            System.out.println("Server is running and waiting for connections...");

            Socket socket = serverSocket.accept();
            System.out.println("Client connected!");

            DataInputStream in = new DataInputStream(socket.getInputStream());
            DataOutputStream out = new DataOutputStream(socket.getOutputStream());
            
            BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

            while (true) {
                System.out.println("\nWaiting for client request...");
                
                // Receiving type of request
                String requestType = in.readUTF();
                if (requestType.equals("file")) {
                    receiveFile(socket, in);
                } else if (requestType.equals("calc")) {
                    performArithmetic(in, out);
                } else if (requestType.equals("exit")) {
                    System.out.println("Client disconnected!");
                    break;
                }
            }

            socket.close();
            serverSocket.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void receiveFile(Socket socket, DataInputStream in) throws IOException {
        System.out.println("Receiving file from client...");
        String fileName = in.readUTF();
        long fileSize = in.readLong();

        FileOutputStream fileOut = new FileOutputStream("server_" + fileName);
        byte[] buffer = new byte[4096];
        int bytesRead = 0;
        long remaining = fileSize;
        
        while ((bytesRead = in.read(buffer, 0, Math.min(buffer.length, (int)remaining))) > 0) {
            fileOut.write(buffer, 0, bytesRead);
            remaining -= bytesRead;
        }
        fileOut.close();
        System.out.println("File received successfully!");
    }

    private static void performArithmetic(DataInputStream in, DataOutputStream out) throws IOException {
        System.out.println("Performing arithmetic operation...");
        String operation = in.readUTF(); // Operation (add, sub, mul, div)
        int num1 = in.readInt();
        int num2 = in.readInt();
        
        int result = 0;
        switch (operation) {
            case "add":
                result = num1 + num2;
                break;
            case "sub":
                result = num1 - num2;
                break;
            case "mul":
                result = num1 * num2;
                break;
            case "div":
                if (num2 != 0) {
                    result = num1 / num2;
                } else {
                    out.writeUTF("Error: Division by zero!");
                    return;
                }
                break;
            default:
                out.writeUTF("Invalid operation!");
                return;
        }
        out.writeUTF("Result: " + result);
    }
}
