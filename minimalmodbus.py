import minimalmodbus

#  What is modbus and write a python program to get the float data from a modbus device
# with baudrate= 9600, read address = 8000, slave ID = 9, port = com1. Use a minimal modbus
# library to achieve the same

instrumentA = minimalmodbus.Instrument('com1', 1)
instrumentA.serial.baudrate = 9600
instrumentA.mode = minimalmodbus.MODE_RTU

instrumentB = minimalmodbus.Instrument('com3', 2)
instrumentB.serial.baudrate = 9600
instrumentB.mode = minimalmodbus.MODE_ASCII

instrumentC = minimalmodbus.Instrument('com4', 1)
instrumentC.serial.baudrate = 9600


instrument = minimalmodbus.Instrument('com1', 8000) # port name, slave address (in decimal)

## Read temperature (PV = ProcessValue) ##
temperature = instrument.read_register(8000, 1) # Registernumber, number of decimals
print(temperature)
