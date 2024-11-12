import java.io.*;
import java.net.*;

public class Client {
    public static void main(String[] args) {
        try {
            Socket socket = new Socket("192.168.83.135", 5000);
            DataInputStream in = new DataInputStream(socket.getInputStream());
            DataOutputStream out = new DataOutputStream(socket.getOutputStream());

            BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

            while (true) {
                System.out.println("\n1. Send File");
                System.out.println("2. Perform Arithmetic Operation");
                System.out.println("3. Exit");
                System.out.print("Enter your choice: ");
                int choice = Integer.parseInt(reader.readLine());

                switch (choice) {
                    case 1:
                        sendFile(socket, out, reader);
                        break;
                    case 2:
                        performArithmetic(out, in, reader);
                        break;
                    case 3:
                        out.writeUTF("exit");
                        System.out.println("Exiting...");
                        socket.close();
                        return;
                    default:
                        System.out.println("Invalid choice!");
                }
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void sendFile(Socket socket, DataOutputStream out, BufferedReader reader) throws IOException {
        System.out.print("Enter file path: ");
        String filePath = reader.readLine();
        File file = new File(filePath);

        if (!file.exists()) {
            System.out.println("File does not exist.");
            return;
        }

        out.writeUTF("file");
        out.writeUTF(file.getName());
        out.writeLong(file.length());

        FileInputStream fileIn = new FileInputStream(file);
        byte[] buffer = new byte[4096];
        int bytesRead = 0;
        while ((bytesRead = fileIn.read(buffer)) > 0) {
            out.write(buffer, 0, bytesRead);
        }

        fileIn.close();
        System.out.println("File sent successfully!");
    }

    private static void performArithmetic(DataOutputStream out, DataInputStream in, BufferedReader reader) throws IOException {
        System.out.print("Enter operation (add, sub, mul, div): ");
        String operation = reader.readLine();
        System.out.print("Enter first number: ");
        int num1 = Integer.parseInt(reader.readLine());
        System.out.print("Enter second number: ");
        int num2 = Integer.parseInt(reader.readLine());

        out.writeUTF("calc");
        out.writeUTF(operation);
        out.writeInt(num1);
        out.writeInt(num2);

        String result = in.readUTF();
        System.out.println(result);
    }
}
