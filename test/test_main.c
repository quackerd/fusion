#include "test_main.h"
#include "test_case.h"
#include <stdio.h>
#include <stdlib.h>

#define GAT_SIZE 256
#define CASE_NUM 32

typedef struct
{
    char *case_name;
    bool success;
    bool used;
} case_info;

static case_info ginfo[CASE_NUM];
static void *gat[GAT_SIZE];
static char *test_name;

static void test_info(void)
{
    printf("[TD-INFO][%s] - ", test_name);
    fflush(stdout);
}

static void test_warning(void)
{
    printf("[TD-WARN][%s] - ", test_name);
    fflush(stdout);
}

static void test_error(void)
{
    printf("[TD-ERR][%s] - ", test_name);
    fflush(stdout);
}

static void gat_push(void *ptr)
{
    for (int i = 0; i < GAT_SIZE; i++)
    {
        if (gat[i] == NULL)
        {
            gat[i] = ptr;
            return;
        }
    }
}

static bool gat_full(void)
{
    for (int i = 0; i < GAT_SIZE; i++)
    {
        if (gat[i] == NULL)
        {
            return FALSE;
        }
    }
    return TRUE;
}

static void gat_free(void)
{
    for (int i = 0; i < GAT_SIZE; i++)
    {
        if (gat[i] != NULL)
        {
            free(gat[i]);
            gat[i] = NULL;
        }
    }
}

static void ginfo_push(char *case_name, bool success)
{
    char *r_case_name = (case_name == NULL ? "Anonymous Case" : case_name);
    for (int i = 0; i < CASE_NUM; i++)
    {
        if (!ginfo[i].used)
        {
            ginfo[i].case_name = r_case_name;
            ginfo[i].success = success;
            ginfo[i].used = TRUE;
            return;
        }
    }
    test_warning();
    printf("GINFO full, [%s] result not recorded.\n", r_case_name);
}

void test_begin(char *name)
{
    test_name = (name == NULL ? "Anonymous Test" : name);
    for (int i = 0; i < GAT_SIZE; i++)
    {
        gat[i] = NULL;
    }
    for (int i = 0; i < CASE_NUM; i++)
    {
        ginfo[i].used = FALSE;
    }
}

void test_end(void)
{
    gat_free();
    int32 total = 0, failed = 0, success = 0;
    for (int i = 0; i < CASE_NUM; i++)
    {
        if (ginfo[i].used)
        {
            total++;
            if (ginfo[i].success)
            {
                success++;
            }
            else
            {
                failed++;
            }
        }
    }
    test_info();
    printf("%s\n", failed > 0 ? "FAIL" : "PASS");
    printf("    %d cases executed. S: %d. F: %d.\n", total, success, failed);
    if (failed > 0)
    {
        for (int i = 0; i < CASE_NUM; i++)
        {
            if (ginfo[i].used && !ginfo[i].success)
            {
                printf("        %s FAILED\n", ginfo[i].case_name);
            }
        }
    }
    for (int i = 0; i < CASE_NUM; i++)
    {
        ginfo[i].used = FALSE;
    }
}

void *talloc(uint32 size)
{
    if (!gat_full())
    {
        void *result = malloc(size);
        gat_push(result);
        return result;
    }
    else
    {
        test_error();
        printf("GAT full, rejecting further allocations.\n");
    }
    return NULL;
}

void run_case(char *name, bool result)
{
    ginfo_push(name, result);
}

int main(void)
{
    linked_list_test();
    salloc_test();
    avl_tree_test();
    return 0;
}


