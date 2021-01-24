import java.io.*;
import java.net.*;
import java.util.IllegalFormatException;


public class RobotModel{
    
    static PrintWriter out;

    public static String linearVelocity = "0.25";
    public static String angularVelocity = "1.00";

    public static void connectToController(){

        try {
            
            Socket socket = new Socket("lear.cs.okstate.edu", 9095);
            out = new PrintWriter(socket.getOutputStream());
     
            out.print("GET /robot_sim.html HTTP/1.1\r\n");
            out.print("host: lear.cs.okstate.edu \r\n\r\n");
            out.flush();
            //socket.close();

        } 
        
        catch (UnknownHostException ex) {
			System.out.println("ERROR: Host URL not recognized.");
		}
		catch (IllegalFormatException ex) {
			System.out.println("ERROR: HTTP response not formatted correctly.");
		}
		
        catch (Exception ex) {
			ex.printStackTrace();
		}
    }


    public static void takeoff(){

        String takeoff_msg = "{\"op\":\"publish\",\"topic\":\"/ardrone/takeoff\",\"msg\":{}}";
        out.println(takeoff_msg);
        out.flush();
    }


    public static void land(){

        String land_msg = "{\"op\":\"publish\",\"topic\":\"/ardrone/land\",\"msg\":{}}";
        out.println(land_msg);
        out.flush();
    }


    public static void forward(){

        String forward_msg = "{\"op\":\"publish\",\"topic\":\"/cmd_vel\",\"msg\":{\"linear\":{\"x\":"
        + linearVelocity + ",\"y\":0,\"z\":0},\"angular\":{\"x\":0,\"y\":0,\"z\":0}}}";

        out.println(forward_msg);
        out.flush();
    }


    public static void backward(){

        String backward_msg = "{\"op\":\"publish\",\"topic\":\"/cmd_vel\",\"msg\":{\"linear\":{\"x\":-"
        + linearVelocity + ",\"y\":0,\"z\":0},\"angular\":{\"x\":0,\"y\":0,\"z\":0}}}";
        
        out.println(backward_msg);
		out.flush();
    }
    

    public static void ascend(){

        String ascend_msg = "{\"op\":\"publish\",\"topic\":\"/cmd_vel\",\"msg\":{\"linear\":{\"x\":0,\"y\":0,\"z\":"
        + linearVelocity + "},\"angular\":{\"x\":0,\"y\":0,\"z\":0}}}";
    
        out.println(ascend_msg);
		out.flush();
    }
    

    public static void descend(){

        String descend_msg = "{\"op\":\"publish\",\"topic\":\"/cmd_vel\",\"msg\":{\"linear\":{\"x\":0,\"y\":0,\"z\":-"
        + linearVelocity + "},\"angular\":{\"x\":0,\"y\":0,\"z\":0}}}";

        out.println(descend_msg);
		out.flush();
    }
    

    public static void left(){

        String left_msg = "{\"op\":\"publish\",\"topic\":\"/cmd_vel\",\"msg\":{\"linear\":{\"x\":0,\"y\":"
        + linearVelocity + ",\"z\":0},\"angular\":{\"x\":0,\"y\":0,\"z\":0}}}";
       
        out.println(left_msg);
		out.flush();
    }

    public static void right(){

        String right_msg = "{\"op\":\"publish\",\"topic\":\"/cmd_vel\",\"msg\":{\"linear\":{\"x\":0,\"y\":-"
        + linearVelocity + ",\"z\":0},\"angular\":{\"x\":0,\"y\":0,\"z\":0}}}";
       
        out.println(right_msg);
		out.flush();
    }

    public static void turnLeft(){

        String turnLeft_msg = "{\"op\":\"publish\",\"topic\":\"/cmd_vel\",\"msg\":{\"linear\":{\"x\":0,\"y\":0,\"z\":0},\"angular\":{\"x\":0,\"y\":0,\"z\":"
        + angularVelocity + "}}}";
       
        out.println(turnLeft_msg);
		out.flush();
    }

    public static void turnRight(){

        String turnRight_msg = "{\"op\":\"publish\",\"topic\":\"/cmd_vel\",\"msg\":{\"linear\":{\"x\":0,\"y\":0,\"z\":0},\"angular\":{\"x\":0,\"y\":0,\"z\":-"
        + angularVelocity + "}}}";
       
        out.println(turnRight_msg);
		out.flush();
    }

    public static void stop(){

        String stop_msg = "{\"op\":\"publish\",\"topic\":\"/cmd_vel\",\"msg\":{\"linear\":{\"x\":0,\"y\":0,\"z\":0},\"angular\":{\"x\":0,\"y\":0,\"z\":0}}}";
       
        out.println(stop_msg);
		out.flush();
    }

    public static void increaseLinearVelocity(){

        double newSpeed = Double.parseDouble(RobotModel.linearVelocity) + .01;
		RobotModel.linearVelocity = (String)String.format("%.2f", newSpeed);
    }

    public static void decreaseLinearVelocity() {
		double newSpeed = Double.parseDouble(RobotModel.linearVelocity) - .01;
		RobotModel.linearVelocity = (String)String.format("%.2f", newSpeed);
    }
    
    public static void increaseAngularVelocity(){

        double newSpeed = Double.parseDouble(RobotModel.angularVelocity) + .01;
		RobotModel.angularVelocity = (String)String.format("%.2f", newSpeed);
    }

    public static void decreaseAngularVelocity() {
		double newSpeed = Double.parseDouble(RobotModel.angularVelocity) - .01;
		RobotModel.angularVelocity = (String)String.format("%.2f", newSpeed);
    }
    
    public static String getLinVelocity(){
        return "                        " + linearVelocity;
    }

    public static String getAngVelocity(){
        return "                        " + angularVelocity;
    }
}