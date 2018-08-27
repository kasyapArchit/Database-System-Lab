pds_contact: pds.o contact.o contact_driver.o
	gcc -o pds_contact pds.o contact.o contact_driver.o

pds.o: pds.h
	gcc -c pds.c

contact.o: pds.h contact.h
	gcc -c contact.c

contact_driver.o: pds.h contact.h
	gcc -c contact_driver.c

clean:
	rm *.o pds_contact
