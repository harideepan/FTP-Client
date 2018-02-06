import java.util.ArrayList;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;
import org.apache.ftpserver.FtpServer;
import org.apache.ftpserver.FtpServerFactory;
import org.apache.ftpserver.ftplet.Authority;
import org.apache.ftpserver.ftplet.FtpException;
import org.apache.ftpserver.ftplet.UserManager;
import org.apache.ftpserver.listener.ListenerFactory;
import org.apache.ftpserver.usermanager.PropertiesUserManagerFactory;
import org.apache.ftpserver.usermanager.impl.BaseUser;
import org.apache.ftpserver.usermanager.impl.WritePermission;
 
public class FTPServer {
    static FtpServer server;
    public static void main(String[] args){
        try {
            FtpServerFactory factory = new FtpServerFactory();
            //PropertiesUserManagerFactory userManagerFactory = new PropertiesUserManagerFactory();
            UserManager userManager = factory.getUserManager();
            BaseUser user = new BaseUser();
            user.setName("Hariharan");
            user.setPassword("");
            user.setHomeDirectory("E:");
            user.setEnabled(true);

            List<Authority> authorities = new ArrayList<Authority>();
            authorities.add(new WritePermission());
            user.setAuthorities(authorities);
            userManager.save(user);
            
            ListenerFactory listenerFactory = new ListenerFactory();
            listenerFactory.setPort(4444);
            factory.setUserManager(userManager);
            factory.addListener("default", listenerFactory.createListener());
            
            server = factory.createServer();
            server.start();
            
        } catch (FtpException ex) {
            Logger.getLogger(FTPServer.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    public static void StopServer()
    {
        server.stop();
    }
}