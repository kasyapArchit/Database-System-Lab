#ifndef PDS_H
#define PDS_H

// Error codes
#define PDS_SUCCESS 0
#define PDS_FILE_ERROR 1
#define PDS_ADD_FAILED 2
#define PDS_REC_NOT_FOUND 3
#define PDS_REPO_ALREADY_OPEN 12
#define PDS_NDX_SAVE_FAILED 13

// Number of index entries in each block
#define BLOCK_SIZE 1024

// Maximum number of index blocks in index file
#define MAX_BLOCKS 1

// Repository status values
#define PDS_REPO_OPEN 10
#define PDS_REPO_CLOSED 11

struct PDS_NdxInfo{
	int key;
	int offset;
};

// Assumption: full index can be loaded into memory
struct PDS_NdxBlock{
	int block_num;
	struct PDS_NdxInfo ndx[BLOCK_SIZE];
};

struct PDS_RepoInfo{
	char pds_name[30];
	FILE *pds_data_fp;
	FILE *pds_ndx_fp;
	int repo_status;
	int num_ndx_blocks;
	int rec_size; // For fixed length records
	struct PDS_NdxBlock ndx_blk;
};

extern struct PDS_RepoInfo repo_handle;

int pds_open( char *repo_name, int rec_size );

// Read index block into memory
int pds_load_primary_ndx();

int put_rec_by_key( int key, void *rec );
int get_rec_by_key( int key, void *rec );
int pds_close();

#endif
