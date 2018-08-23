#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>

#include "contact.h"
#include "pds.h"

// Define the global variable
struct PDS_RepoInfo repo_handle;

int pds_open( char *repo_name )
{
	char repo_file[30];

	// Check if status is already open in repo_handle
	if( repo_handle.repo_status == PDS_REPO_OPEN)// TO-DO )
		return PDS_REPO_ALREADY_OPEN;

	strcpy(repo_handle.pds_name,repo_name);

	strcpy(repo_file,repo_name);
	strcat(repo_file,".dat");

	// Open the repository file in binary read-write mode
	repo_handle.pds_data_fp = fopen(repo_file, "ab+");// TO-DO
	if( repo_handle.pds_data_fp == NULL ){
		perror(repo_file);
	}

	repo_handle.repo_status = PDS_REPO_OPEN;// TO-DO set the status appropriately from pds.h
	return PDS_SUCCESS;
}

// Seek to the end of the data file
// Write the record at the current file location
// Set status to PDS_SUCCESS on success or appropriate error status as defined in pds.h

int put_rec_by_key( int key, struct Contact *rec )
{
	int offset, status, writesize;

	// TO-DO
	offset = 0;
	status = PDS_ADD_FAILED;
	writesize = sizeof(struct Contact);

	fseek(repo_handle.pds_data_fp, offset, SEEK_END);
	if(fwrite(rec, writesize, 1, repo_handle.pds_data_fp)==1)
		status = PDS_SUCCESS;

	return status;
}

// Read one-record-at a time in a loop until EOF from the beginning of the file
// Compare the key of the record being read with the key being searched
// Set status to PDS_SUCCESS on success or appropriate error status as defined in pds.h

int get_rec_by_key( int key, struct Contact *rec )
{
	int offset, status, readsize;

	// TO-DO
	offset = 0;
	readsize = sizeof(struct Contact);
	struct Contact *tmp = (struct Contact*)malloc(readsize);
	fseek(repo_handle.pds_data_fp, offset, SEEK_SET);

	while(fread(tmp, readsize, 1, repo_handle.pds_data_fp)==1)
	{
		if(tmp->contact_id == key)
		{
			status = PDS_SUCCESS;
			*rec = *tmp;
		}
	}
	free(tmp);
	if(!feof(repo_handle.pds_data_fp))
		status = PDS_FILE_ERROR;
		
	return status;
}

int pds_close()
{
	strcpy(repo_handle.pds_name, "");
	fclose(repo_handle.pds_data_fp);
	repo_handle.repo_status = PDS_REPO_CLOSED;

	return PDS_SUCCESS;
}
