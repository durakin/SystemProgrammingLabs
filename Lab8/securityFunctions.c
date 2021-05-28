/*! \file   securityFunctions.c
 *  \brief  Implements functions from securityFunctions.c
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <security/pam_appl.h>
#include <security/pam_misc.h>
#include "securityFunctions.h"
#include "serverFunctions.h"


void CheckRoot()
{
    if (geteuid() != 0)
    {
        fprintf(stderr, "Server can only be started by root\n");
        exit(EXIT_FAILURE);
    }
    if (access(PATH_TO_CHECK_FILE, F_OK) == 0)
    {
        remove(PATH_TO_CHECK_FILE);
    }
}

void CheckAuthentication()
{
    pam_handle_t* pamh;
    struct pam_conv pamc;
    pamc.conv = &misc_conv;
    pamc.appdata_ptr = NULL;
    pam_start("su", getenv("USER"), &pamc, &pamh);
    if (pam_authenticate(pamh, 0) != PAM_SUCCESS)
    {
        fprintf(stderr,"Authentication fail\n");
        exit(EXIT_FAILURE);
    }
    pam_end(pamh, 0);
}