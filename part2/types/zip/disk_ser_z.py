import sys
sys.path.append("gen-py")

from thrift.transport import TTransport
from thrift.transport import TZlibTransport
from thrift.protocol import TBinaryProtocol
from radio_observation import ttypes

#Read in the serialized compressed UDT
ep_trans = TTransport.TFileObjectTransport(open("data.z","rb"))
trans = TZlibTransport.TZlibTransport(ep_trans)
trans.open()
proto = TBinaryProtocol.TBinaryProtocol(trans)
ro = ttypes.RadioObservation()
ro.read(proto)
trans.close()

#Display the contents of the UDT
print("\nReading Observations")
print("-------------------------")
print("Telescope Count: %d" % ro.telescope_count)
print("System         : %s" % ttypes.RadioObservationSystem._VALUES_TO_NAMES[ro.system])
print("Time           : %f" % ro.time)
if None != ro.pos.icrfpos:
    print("Position       : %f dec - %f ra [%s]" % 
      (ro.pos.icrfpos.declination, 
       ro.pos.icrfpos.right_ascension, 
       "" if None == ro.pos.icrfpos.ecliptic_year else str(ro.pos.icrfpos.ecliptic_year)))
print("Frequency   Magnitude")
for k,v in ro.freq_amp.items():
    print("  %d  %f" % (k,v))
print("Size of bmp: %d" % (0 if None == ro.sky_bmp else len(ro.sky_bmp)))

#Close the source file and write a compressed copy of the UDT to a backup file
ep_trans = TTransport.TFileObjectTransport(open("data.z.bak","wb"))
trans = TZlibTransport.TZlibTransport(ep_trans)
trans.open()
proto = TBinaryProtocol.TBinaryProtocol(trans)
ro.write(proto)
trans.flush()
trans.close()

