pds_tester: pds_tester.o pds.o contact.o bst.o
	gcc -o pds_tester pds_tester.o pds.o contact.o bst.o

contact_driver: contact_driver.o pds.o contact.o bst.o
	gcc -o contact_driver contact_driver.o pds.o contact.o bst.o

contact_loader: contact_loader.o pds.o contact.o bst.o
	gcc -o contact_loader contact_loader.o pds.o contact.o bst.o

bst_main: bst_main.o bst.o
	gcc -o bst_main bst_main.o bst.o

bst_main.o: bst_main.c bst.h
	gcc -c bst_main.c

contact_loader.o: contact_loader.c contact.h pds.h bst.h
	gcc -c contact_loader.c

contact_driver.o: contact_driver.c contact.h pds.h bst.h
	gcc -c contact_driver.c

pds_tester.o: pds_tester.c pds.h contact.h bst.h
	gcc -c pds_tester.c

bst.o: bst.c
	gcc -c bst.c

pds.o: pds.c bst.h
	gcc -c pds.c

contact.o: contact.c pds.h bst.h
	gcc -c contact.c
