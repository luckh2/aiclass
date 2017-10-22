instrhwinfo('bluetooth')
instrhwinfo('bluetooth','BT04-A')
b=Bluetooth('BT04-A',1);
fopen(b);
fwrite(b,'101X');
