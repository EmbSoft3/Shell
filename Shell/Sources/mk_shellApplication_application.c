/**
*
* @copyright Copyright (C) 2024 RENARD Mathieu. All rights reserved.
*
* This file is part of Mk.
*
* Mk is free software. Redistribution and use in source and binary forms, with or
* without modification, are permitted provided that the following conditions are
* met:
*
*    1. Redistributions of source code must retain the above copyright notice,
*       this list of conditions and the following disclaimer.
*    2. Redistributions in binary form must reproduce the above copyright notice,
*       this list of conditions and the following disclaimer in the documentation
*       and/or other materials provided with the distribution.
*    3. Neither the name of the copyright holder nor the names of its contributors
*       may be used to endorse or promote products derived from this software
*       without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
* LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
* OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
* ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
* @file mk_shellApplication_application.c
* @brief Déclaration des données applicatives de l'application Shell.
* @date 4 août 2024
*
*/

#include "mk.h"
#include "mk_shell_constants.h"
#include "mk_shell_types.h"
#include "mk_shellApplication_constants.h"
#include "mk_shellApplication_types.h"
#include "mk_shellApplication_data.h"
#include "mk_shellApplication.h"

/**
 * @def K_MK_SECTION_STACK
 * @brief Cette constante définit la zone mémoire où la pile de l'application doit être allouée. \n
 */

#define K_MK_SECTION_STACK __attribute__ ((section(".stack"),used))

/**
 * @def K_MK_SECTION_STACK
 * @brief Cette constante définit la zone mémoire où le descripteur d'application doit être alloué. \n
 */

#define K_MK_SECTION_DESCRIPTOR __attribute__ ((section(".descriptor"),used))

/**
 * @internal
 * @brief
 * @endinternal
 */

K_MK_SECTION_STACK uint32_t g_mkStack [ K_MK_SHELL_APPLICATION_STACK_SIZE ];

/**
 * @internal
 * @brief
 * @endinternal
 */

/* Déclaration d'un descripteur d'application */
K_MK_SECTION_DESCRIPTOR T_mkApplicationDynamicHeader g_mkApplicationDynamicHeader =
{
   /* Entête de l'application */
   {
      K_MK_DISPLAY_APPLICATION_DYNAMICHEADER_MAGICNUMBER,      /* Magic Number */
      sizeof ( T_mkApplicationDynamicHeader ),                 /* Taille de l'entête */
      0xFFFFFFFF,                                              /* Reserved */
      1,                                                       /* Version */
      &g_mkApplicationDynamicHeader.descriptor,                /* Adresse du descripteur */
      sizeof ( T_mkApplicationDescriptor ),                    /* Taille du descripteur */
      &g_mkApplicationDynamicHeader.metadata,                  /* Adresse des métadonnées */
      sizeof ( T_mkApplicationMetadata ),                      /* Taille des métadonnées */
      &g_mkApplicationDynamicHeader.args,                      /* Adresse de la structure stockant les arguments saisis en ligne de commande */
      sizeof ( T_mkApplicationCmdLineArguments )               /* Taille de la structure stockant les arguments saisis en ligne de commande */
   },

   /* Descripteur d'application */
   {
      K_MK_APPLICATION_TYPE_DYNAMIC,                           /* Application graphique dynamique */
      K_MK_TYPE_FLOATING_PRIVILEGED,                           /* Tâche flottante privilégiée. */
      K_MK_TRUE,                                               /* Allocation d'une page mémoire graphique */
      K_MK_FALSE,                                              /* Pas d'allocation de page mémoire standard */
      g_mkStack,                                               /* Adresse de la stack */
      K_MK_SHELL_APPLICATION_STACK_SIZE,                       /* Taille de la stack. */
      mk_shellApplication_main,                                /* Point d'entrée de l'application */
      K_MK_NULL                                                /* Argument de l'application (application statique uniquement) */
   },

   /* Métadonnées de l'application */
   {
      ( T_str8 ) "Shell",                                      /* Nom de l'application. */
      ( T_str8 ) "Mac Lewis",                                  /* Auteur de l'application. */
      ( T_str8 ) "V1.1",                                       /* Version de l'application. */
      ( T_str8 ) "Command line interface (CLI).",              /* Description de l'application. */
      ( T_str8 ) "mk_shell.bmp",                               /* Chemin relatif vers l'icône de l'application. */
      K_MK_NULL                                                /* Adresse d'un bitmap */
   },

   /* Arguments de l'application */
   {
      { 0 }                                                    /* Chaine de caractères contenant les arguments saisis en ligne de commande */
   }
};


