	cseg at 0x6500  ;//36 bytes Inquiry string 

    db 0x00, 0x80, 0x02, 0x02, 0x00, 0x00, 0x00, 0x00 
	db 'J','I','E',' ','L','I',' ',' ' 
	db 'M', 'u', 's', 'i', 'c', ' ', 'P', 'l', 'a', 'y', 'e', 'r', ' ', ' ', ' ', ' ' 
	db 0x31, 0x2e, 0x30, 0x30			//version

	cseg at (0x6500 + 36)
	///MANUFACTURE string
	db 16, 0x03, 'A',0,'C',0,'3',0,'0',0, '9',0,'N',0,' ',0

end