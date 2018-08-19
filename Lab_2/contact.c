#include<stdio.h>
#include<stdlib.h>

#include "pds.h"
#include "contact.h"

// Load all the contacts from a CSV file
int store_contacts( char *contact_data_file )
{
	FILE *cfptr;
	char contact_line[500], token;
	struct Contact c, dummy;

	cfptr = (FILE *) fopen(contact_data_file, "r");
	while(fgets(contact_line, sizeof(contact_line)-1, cfptr)){
		//printf("line:%s",contact_line);
		sscanf(contact_line, "%d%s%s", &(c.contact_id),c.contact_name,c.phone);
		print_contact( &c );
		add_contact( &c );
	}
}

void print_contact( struct Contact *c )
{
	printf("%d,%s,%s\n", c->contact_id,c->contact_name,c->phone);
}

// Use get_rec_by_key function to retrieve contact
int search_contact( int contact_id, struct Contact *c )
{
	int status;

	status = get_rec_by_key( contact_id, c );

	if( status == PDS_SUCCESS )
		status = CONTACT_SUCCESS;
	else
		status = CONTACT_FAILURE;

	return status;
}

// Add the given contact into the repository by calling put_rec_by_key
int add_contact( struct Contact *c )
{
	int status;

	// TO-DO: call put_rec_by_key to store the contact
	status = // TO-DO

	if( status != PDS_SUCCESS ){
		fprintf(stderr, "Unable to add contact with key %d. Error %d", c->contact_id, status );
		status=//TO-DO: Return appropriate success/failure status from contact.h
	}
	else
		status=//TO-DO: Return appropriate success/failure status from contact.h

	return status;
}
