import java.nio.file.Files;
import java.nio.file.Paths;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;
import org.apache.thrift.TException;
import org.apache.thrift.transport.TTransport;
import org.apache.thrift.transport.TZlibTransport;
import org.apache.thrift.transport.TSimpleFileTransport;
import org.apache.thrift.protocol.TBinaryProtocol;
import org.apache.thrift.protocol.TProtocol;
import radio_observation.ICRFPosition;
import radio_observation.Position;
import radio_observation.RadioObservation;
import radio_observation.RadioObservationSystem;
import radio_observation.radio_observationConstants;


public class DiskSerZ {
  public static void FakeInit(RadioObservation ro) {
      ro.telescope_count = 1;
      ro.system = RadioObservationSystem.Arecibo;
      ro.time = System.currentTimeMillis() / 1000.0;
      ICRFPosition pos = new ICRFPosition(270.3, 45.24);
      pos.setEcliptic_year((short)2000);
      ro.pos = new Position();
      ro.pos.setIcrfpos(pos);
      ro.freq_amp = new HashMap<>();
      ro.freq_amp.put(20500000L, 75.456);
      ro.freq_amp.put(50000000L, 29.321);
      ro.freq_amp.put(75000000L, 51.526);
  }
  
  public static void DumpICRFPosition(ICRFPosition pos) {
      System.out.println("Position       : " + 
                         pos.declination + " dec - " + 
                         pos.right_ascension + " ra [" + 
                         ((pos.isSetEcliptic_year())?pos.ecliptic_year:"") + "]");    
  }
  
  public static void DumpObservation(RadioObservation ro) {
      System.out.println("Telescope Count: " + ro.telescope_count);
      System.out.println("System         : " + ro.system.name());
      System.out.println("Time           : " + ro.time);
      if (ro.pos.isSetIcrfpos()) {
          DumpICRFPosition(ro.pos.getIcrfpos());
      }
      System.out.println("Frequency   Magnitude");
      for (Map.Entry<Long, Double> entry : ro.freq_amp.entrySet()) {
          System.out.println("  "+entry.getKey()+"  "+entry.getValue());
      }      
  }
  
  public static void WriteRadioObservation(TProtocol proto, 
                                           boolean writeBMP) 
          throws TException, IOException {
      System.out.println("\nWriting Observations");
      System.out.println("-------------------------");
      RadioObservation ro = new RadioObservation();
      FakeInit(ro);
      if (writeBMP){
        ro.setSky_bmp(Files.readAllBytes(Paths.get("quasar.bmp")));       
      }
      ro.write(proto);
      proto.getTransport().flush();
      DumpObservation(ro);    
  }

  public static void ReadRadioObservation(TProtocol proto) throws TException {
      System.out.println("\nReading Observations");
      System.out.println("-------------------------");
      RadioObservation ro = new RadioObservation();
      ro.read(proto);
      DumpObservation(ro);    
  }

  public static void main(String[] args) {
    TTransport trans = null;
    try {
      System.out.println("Radio Observation Disk Serializer " + radio_observationConstants.Version);
      trans = new TSimpleFileTransport("data.z", true, true);
      trans = new TZlibTransport(trans);
      trans.open();
      TProtocol proto = new TBinaryProtocol(trans);
      if (args.length > 0 && 0 == args[0].compareTo("write")) {
        WriteRadioObservation(proto, args.length > 1);        
      } else if (args.length>0 && 0==args[0].compareToIgnoreCase("read")) {
        ReadRadioObservation(proto);      
      }
      else {
         System.out.println("Usage: DiskSer (read | write [bmp])");        
      }
    } catch (TException | IOException ex) {
      System.out.println("Error: " + ex.getMessage());
    }
    if (null != trans) {
      trans.close();
    }
  }
}
