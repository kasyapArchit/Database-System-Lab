#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>

// #include "contact.h"
#include "pds.h"

// Define the global variable
struct PDS_RepoInfo repo_handle;
struct PDS_NdxInfo ndx;

int pds_open( char *repo_name, int rec_size )
{
	repo_handle.rec_size = rec_size;
	char repo_file[30], repo_ndx_file[30];

	// Check if status is already open in repo_handle
	if( repo_handle.repo_status == PDS_REPO_OPEN)// TO-DO )
		return PDS_REPO_ALREADY_OPEN;

	strcpy(repo_handle.pds_name,repo_name);

	strcpy(repo_file,repo_name);
	strcat(repo_file,".dat");
	strcpy(repo_ndx_file,repo_name);
	strcat(repo_ndx_file,".ndx");

	// Open the repository file and index in binary read-write mode
	repo_handle.pds_data_fp = fopen(repo_file, "ab+");// TO-DO
	repo_handle.pds_ndx_fp = fopen(repo_ndx_file, "ab+");
	if( repo_handle.pds_data_fp == NULL ){
		perror(repo_file);
	}

	repo_handle.repo_status = PDS_REPO_OPEN;// TO-DO set the status appropriately from pds.h
	return PDS_SUCCESS;
}

int pds_load_primary_ndx()
{
	// TO-DO

	return 1;
}

// Seek to the end of the data file
// Write the record at the current file location
// Set status to PDS_SUCCESS on success or appropriate error status as defined in pds.h

int put_rec_by_key( int key, void *rec )
{
	int offset, status, writesize;

	// TO-DO
	if(repo_handle.repo_status != PDS_REPO_OPEN)
		return PDS_ADD_FAILED;
	offset = 0;
	status = PDS_ADD_FAILED;
	writesize = repo_handle.rec_size;
	fseek(repo_handle.pds_data_fp, offset, SEEK_END);
	ndx.key = key;
	ndx.offset = ftell(repo_handle.pds_data_fp);

	if(fwrite(rec, writesize, 1, repo_handle.pds_data_fp)==1)
		status = PDS_SUCCESS, fflush(stdout);
	else
		return status;
	if(fwrite(&ndx, sizeof(struct PDS_NdxInfo), 1, repo_handle.pds_ndx_fp)!=1)
		status = PDS_NDX_SAVE_FAILED;
	fflush(stdout);
	return status;
}

// Read one-record-at a time in a loop until EOF from the beginning of the file
// Compare the key of the record being read with the key being searched
// Set status to PDS_SUCCESS on success or appropriate error status as defined in pds.h

int get_rec_by_key( int key, void *rec )
{
	int offset, status, readsize;

	// TO-DO
	status = PDS_REC_NOT_FOUND;
	if(repo_handle.repo_status != PDS_REPO_OPEN)
		return PDS_REC_NOT_FOUND;
	readsize = sizeof(struct PDS_NdxInfo);
	struct PDS_NdxInfo *tmp = (struct PDS_NdxInfo*)malloc(readsize);

	fseek(repo_handle.pds_ndx_fp, 0, SEEK_SET);

	while(fread(tmp, readsize, 1, repo_handle.pds_ndx_fp)==1)
	{
		if(tmp->key == key)
		{
			status = PDS_SUCCESS;
			offset = tmp->offset;
			fseek(repo_handle.pds_data_fp, offset, SEEK_SET);
			fread(rec, repo_handle.rec_size, 1, repo_handle.pds_data_fp);
			break;
		}
	}
	free(tmp);
	return status;
}

int pds_close()
{
	strcpy(repo_handle.pds_name, "");
	fclose(repo_handle.pds_data_fp);
	fclose(repo_handle.pds_ndx_fp);
	repo_handle.repo_status = PDS_REPO_CLOSED;

	return PDS_SUCCESS;
}
