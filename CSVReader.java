
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.util.ArrayList;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;



public class CSVReader
{
    List<String> fileContent;
    List<String> filteredContent;
    String currentSearchKey;
    String fileName;
    int rows;
    int columns;
    int filteredRows;
    static int maxLoadCount=30;
    
    int startOfFileContent;
    int endOfFileContent;
    int startOfFilteredContent;
    int endOfFilteredContent;
    
    boolean fileContentEnd;
    boolean filteredContentEnd;
    
    public CSVReader(String fileName)
    {
        try {
            this.fileName=fileName;
            currentSearchKey="";
            File file = new File(fileName);
            filteredContent=new ArrayList<String>();
            fileContent = Files.readAllLines(file.toPath(), StandardCharsets.UTF_8);
            rows=fileContent.size();
            startOfFileContent=rows!=0?0:-1;
            endOfFileContent=(rows>maxLoadCount?maxLoadCount-1:rows-1);
            if(rows!=0)
            {
                String[] array=fileContent.get(0).split(",");
                columns=array.length;
            }
        } catch (IOException ex) {
            Logger.getLogger(CSVReader.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    public String[][] getFileContent()
    {
        if(startOfFileContent!=endOfFileContent)
        {
            String[][]file=new String[endOfFileContent-startOfFileContent+1][columns];
            int i,j,k=0;
            for (i=startOfFileContent;i<=endOfFileContent;i++)
            {
                String line=fileContent.get(i);
                String[] array = line.split(",");
                for(j=0;j<array.length;j++)
                    file[k][j]=array[j];
                k++;
            }
            startOfFileContent+=(startOfFileContent+maxLoadCount>=rows?endOfFileContent-startOfFileContent:maxLoadCount);
            endOfFileContent+=(endOfFileContent+maxLoadCount>=rows?rows-1-endOfFileContent:maxLoadCount);
            return file;
        }
        else
        {
            return new String[0][0];
        }
    }
    
    public String[][] getFilteredContent(String searchKey)
    {
        if(!currentSearchKey.equals(searchKey))
        {
            currentSearchKey=searchKey;
            startOfFilteredContent=0;
            endOfFilteredContent=maxLoadCount-1;
            filter(searchKey);
        }
        if(startOfFilteredContent!=endOfFilteredContent)
        {
            String[][] file=new String[endOfFilteredContent-startOfFilteredContent+1][columns];
            int i,j,k=0;
            for (i=startOfFilteredContent;i<=endOfFilteredContent;i++)
            {
                String line=filteredContent.get(i);
                String[] array = line.split(",");
                for(j=0;j<array.length;j++)
                    file[k][j]=array[j];
                k++;
            }
            startOfFilteredContent+=(startOfFilteredContent+maxLoadCount>=filteredRows?endOfFilteredContent-startOfFilteredContent:maxLoadCount);
            endOfFilteredContent+=(endOfFilteredContent+maxLoadCount>=filteredRows?filteredRows-1-endOfFilteredContent:maxLoadCount);
            return file;
        }
        else
        {
            return new String[0][0];
        }
    }
    
    public String[][] loadMore()
    {
        if(!this.filteredContent.isEmpty())
        {
            return getFilteredContent(currentSearchKey);
        }
        else
        {
            return getFileContent();
        }
    }
    
    public void filter(String searchKey)
    {   
        int i=0,j,k;
        this.filteredContent=new ArrayList<String>();
        for (String line:fileContent)
        {
            String[] array = line.split(",");
            for(j=0;j<array.length;j++)
            {
                if(i==0)
                {
                    this.filteredContent.add(line);
                    i++;
                    break;  
                }
                else
                {    
                    if(array[j].contains(searchKey))
                    {
                        this.filteredContent.add(line);
                        i++;
                        break;
                    }
                }
            }   
        }
        this.filteredRows=i;
        startOfFileContent=filteredRows!=0?0:-1;
        endOfFilteredContent=(filteredRows>maxLoadCount?maxLoadCount-1:filteredRows-1);
    }
    public void export(String toFileName)
    {
        FileWriter writer = null;
        try {
            File file = new File(toFileName);
            if (file.createNewFile()){
                System.out.println("File is created!");
            }
            else{
                System.out.println("File already exists.");
            }   
            writer = new FileWriter(file);
            if(!this.filteredContent.isEmpty())
            {   
                for(String line:this.filteredContent)
                {
                    writer.write(line + "\n");
                }
                //writer.write("written filteredContent");
            }
            else
            {
                for(String line:this.fileContent)
                {
                    writer.write(line + "\n");
                }
                //writer.write("written fileContent");
            }
            writer.close();
        } catch (IOException ex) {
            Logger.getLogger(CSVReader.class.getName()).log(Level.SEVERE, null, ex);
        } finally {
            try {
                writer.close();
            } catch (IOException ex) {
                Logger.getLogger(CSVReader.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
    }
}