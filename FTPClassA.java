/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */



/**
 *
 * @author hari-pt1933
 */
import org.apache.commons.net.ftp.FTPClient;
import org.apache.commons.net.ftp.FTPFile;
import org.apache.commons.net.PrintCommandListener;
import org.apache.commons.net.ftp.FTP;
import org.apache.commons.net.ftp.FTPReply;
import org.apache.commons.net.ftp.FTPFile;


import java.io.IOException;
import java.util.logging.Level;
import java.util.logging.Logger;
import java.util.TimerTask;
import java.io.File;
import java.io.FileInputStream;
import java.io.InputStream;
import java.io.PrintWriter;
import java.io.FileOutputStream;
import java.util.Timer;

class FTPClassA
{
    FTPClient ftp = null;
    long timestamp;
    
    public FTPClassA()
    {
        int reply;
		ftp = new FTPClient();
        try {
            ftp.connect("localhost",4444);
        } catch (IOException ex) {
            Logger.getLogger(FTPClassA.class.getName()).log(Level.SEVERE, null, ex);
        }
        reply = ftp.getReplyCode();
        if (!FTPReply.isPositiveCompletion(reply)) {
            try {
                ftp.disconnect();
                throw new Exception("Exception in connecting to FTP Server");
            } catch (Exception ex) {
                Logger.getLogger(FTPClassA.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
        ftp.enterLocalPassiveMode();
        try {
            ftp.login("Hariharan", "");
        } catch (IOException ex) {
            Logger.getLogger(FTPClassA.class.getName()).log(Level.SEVERE, null, ex);
        }
	ftp.enterLocalPassiveMode();
    }
    public void createDirectory(String dir)
    {
        try {
            boolean i=ftp.makeDirectory("/Users/"+ dir);
            if(i)
                System.out.print("Created dir");
            else
                System.out.print("no dir");
        } catch (IOException ex) {
            Logger.getLogger(FTPClassA.class.getName()).log(Level.SEVERE, null, ex);
        } catch (Exception ex) {
            Logger.getLogger(FTPClassA.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    public void uploadFile(String localFileFullName, String fileName, String hostDir)
    {
	try{
            try(InputStream input = new FileInputStream(new File(localFileFullName))) 
            {
                ftp.storeFile(hostDir + fileName, input);
		System.out.print("file stored");
            }
        }   catch (IOException ex) {
            Logger.getLogger(FTPClassA.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    public void downloadFile(String remoteFilePath, String localFilePath) 
    {
        try 
        {
            try (FileOutputStream fos = new FileOutputStream(localFilePath))
            {
                FTPFile file =ftp.mdtmFile(remoteFilePath);
                this.timestamp=file.getTimestamp().getTimeInMillis();
                ftp.retrieveFile(remoteFilePath, fos);
            }
            catch (IOException e) {e.printStackTrace();}
        } 
        catch (Exception ex) {Logger.getLogger(FTPClassA.class.getName()).log(Level.SEVERE, null, ex);}
        
    }
    public int isChanged(String remoteFilePath)
    {
        try {
            FTPFile file =ftp.mdtmFile(remoteFilePath);
            long timestamp=file.getTimestamp().getTimeInMillis();
            if(this.timestamp!=timestamp)
            {
                this.timestamp=timestamp;
                return 1;
            }
        } catch (IOException ex) {
            Logger.getLogger(FTPClassA.class.getName()).log(Level.SEVERE, null, ex);
        }
        return 0;
    }
	public String[] getFileList(String userID)
    {
		String[] fileList=null;
        int l;
        try {
            FTPFile[] files = ftp.listFiles("/Users/"+userID);
            l=files.length;
            fileList=new String[files.length];
            int count=0;
            for (FTPFile file : files) {
                if (file.getType() == FTPFile.FILE_TYPE)
                System.out.println(file.getName());
                    fileList[count++]=file.getName();
            }
        } catch (IOException ex) {
            Logger.getLogger(FTPClassA.class.getName()).log(Level.SEVERE, null, ex);
        }
        return fileList;
    }  
    public void disconnectFTP()
    {
        if (ftp.isConnected()) {
            try 
            {
                    ftp.logout();
                    ftp.disconnect();
            } 
            catch (IOException e) {e.printStackTrace();}
	}
    }
}


