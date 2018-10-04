#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>

#include "bst.h"
#include "pds.h"

// Define the global variable
struct PDS_RepoInfo repo_handle;

// Open data file, (if repo_name is "demo", then data file name is demo.dat)
// Open index file (if repo_name is "demo", index file is demo.ndx)
// Load data from index file into Binary Search Tree variable present in the repo handle

int pds_open( char *repo_name, int rec_size )
{
	int status;
	char repo_file[30];
	char indx_file[30];
	if (repo_handle.repo_status == PDS_REPO_OPEN)
    return PDS_REPO_ALREADY_OPEN;

	strcpy(repo_handle.pds_name, repo_name);
	repo_handle.rec_size = rec_size;

	strcpy(repo_file, repo_name);
  strcat(repo_file, ".dat");
  repo_handle.pds_data_fp = fopen(repo_file, "ab+");

	strcpy(indx_file, repo_name);
	strcat(indx_file, ".ndx");
	repo_handle.pds_ndx_fp = fopen(indx_file, "ab+");

	if (repo_handle.pds_data_fp == NULL) {
		perror(repo_file);
	}

	if (repo_handle.pds_ndx_fp == NULL) {
		perror(indx_file);
	}

	fseek(repo_handle.pds_ndx_fp, 0, SEEK_SET);
	repo_handle.pds_bst = NULL;

	struct PDS_NdxInfo *inf = (struct PDS_NdxInfo *) malloc(sizeof(struct PDS_NdxInfo));
	while (fread(inf, sizeof(struct PDS_NdxInfo), 1, repo_handle.pds_ndx_fp)) {
    	if (!feof(repo_handle.pds_ndx_fp)) {
				bst_add_node(&repo_handle.pds_bst, inf->key, inf);
				inf = (struct PDS_NdxInfo *) malloc(sizeof(struct PDS_NdxInfo));
    	}
  }
	repo_handle.repo_status = PDS_REPO_OPEN;
		return PDS_SUCCESS;
}

// Seek to the end of the data file
// Create an index entry with the current file location
// Add index entry to BST
// Write the record at the current file location

int put_rec_by_key( int key, void *rec )
{
	int offset, status, writesize;
	struct PDS_NdxInfo *ndx_entry;

	status = fseek(repo_handle.pds_data_fp, 0, SEEK_END);
	offset = ftell(repo_handle.pds_data_fp);
	status = fwrite(rec, repo_handle.rec_size, 1, repo_handle.pds_data_fp);

	ndx_entry = (struct PDS_NdxInfo *) malloc(sizeof(struct PDS_NdxInfo));
  ndx_entry->key = key;
  ndx_entry->offset = offset;

	status = bst_add_node(&repo_handle.pds_bst, ndx_entry->key, ndx_entry);


	return PDS_SUCCESS;
}

// Search for index entry in BST
// Seek to the file location based on offset in index entry
// Read the record at the current file location

int get_rec_by_key( int key, void *rec )
{
	struct PDS_NdxInfo *ndx_entry;
	struct BST_Node *bst_node;
	int offset, status, readsize;

	bst_node = bst_search(repo_handle.pds_bst, key);
	if (bst_node == NULL){
		return PDS_REC_NOT_FOUND;
	}

	ndx_entry=(struct PDS_NdxInfo *)bst_node->data;
	offset=ndx_entry->offset;

	status = fseek(repo_handle.pds_data_fp, offset, SEEK_SET);
	fread(rec, repo_handle.rec_size, 1, repo_handle.pds_data_fp);

	return PDS_SUCCESS;
}

// Search for index entry in BST
// Delete from BST, delete from data file

int delete_rec_by_key( int key )
{
	struct PDS_NdxInfo *ndx_entry;
	struct BST_Node *bst_node;
	int offset, status, readsize;

	bst_node = bst_search(repo_handle.pds_bst, key);
	status = -100;

	if (bst_node != NULL){
		ndx_entry = (struct PDS_NdxInfo*)(bst_node->data);
		offset = ndx_entry->offset;
		bst_delete(&repo_handle.pds_bst, key);
		if(bst_search(repo_handle.pds_bst, key) == NULL){
			status = PDS_SUCCESS;
		}
	}
	else{
		status = PDS_SUCCESS;
	}
	return status;
}

// Close file pointers
// Free BST index
// Clear data in repo handle
// Update repository status in repo handle
static void preorder(struct BST_Node *root)
{
	if(root == NULL)
		return;

	fwrite(root->data, sizeof(struct PDS_NdxInfo), 1, repo_handle.pds_ndx_fp);
	fseek(repo_handle.pds_ndx_fp, 0, SEEK_END);

	preorder(root->left_child);
	preorder(root->right_child);
}

int pds_close()
{
	fclose(repo_handle.pds_data_fp);
	fclose(repo_handle.pds_ndx_fp);

	char indx_file[30];

	strcpy(indx_file, repo_handle.pds_name);
	strcat(indx_file, ".ndx");
	repo_handle.pds_ndx_fp = fopen(indx_file, "wb");
	preorder(repo_handle.pds_bst);
	fclose(repo_handle.pds_ndx_fp);

	bst_free(repo_handle.pds_bst);
	strcpy(repo_handle.pds_name, "");
	repo_handle.repo_status = PDS_REPO_CLOSED;

	return PDS_SUCCESS;
}
