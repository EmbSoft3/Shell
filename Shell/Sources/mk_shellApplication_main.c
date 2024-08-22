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
* @file mk_shellApplication_main.c
* @brief Déclaration de la fonction mk_shellApplication_main.
* @date 4 août 2023
*
*/

#include "mk.h"
#include "mk_shell_constants.h"
#include "mk_shell_types.h"
#include "mk_shell_private.h"
#include "mk_shellApplication_constants.h"
#include "mk_shellApplication_types.h"
#include "mk_shellApplication_data.h"
#include "mk_shellApplication.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_shellApplication_initAsciiArt ( T_mkShellApplication* p_shell )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Effacement de la console */
   l_result = mk_console_clean ( &p_shell->console );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Affichage du message d'acceuil */
      l_result  = mk_console_puts ( &p_shell->console, ( T_str8 ) "\nMkSoft Command Line Interface (CLI).\n");
      l_result |= mk_console_puts ( &p_shell->console, ( T_str8 ) "Copyright (C) 2024 RENARD Mathieu. All rights reserved.\n" );
      l_result |= mk_console_puts ( &p_shell->console, ( T_str8 ) "This is free software; see the source for copying conditions.\n" );
      l_result |= mk_console_print ( &p_shell->console, ( T_str8 ) "Use the help command to display the command set.\n\n" );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

void mk_shellApplication_main ( T_mkAddr p_param )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un message */
   T_mkShellMessage l_message;

   /* Récupération de l'adresse de l'application */
   T_mkApplication* l_application = ( T_mkApplication* ) p_param;

   /* Initialisation de l'application */
   l_result = mk_shellApplication_init ( &g_mkShellApplication, l_application );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Affichage du message d'acceuil */
      l_result = mk_shellApplication_initAsciiArt ( &g_mkShellApplication );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Boucle tant qu'aucune erreur ne s'est produite */
   while ( l_result == K_MK_OK )
   {
      /* Analyse de la boite de messages pour savoir si une nouvelle commande est disponible */
      l_result = mk_mail_pend ( K_MK_NULL, g_mkShellApplicationMessageArea.mail, ( T_mkAddr ) &l_message, K_MK_TASK_WAIT_FOREVER );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Analyse et exécution de la commande */
         /* On bypass le code de retour */
         ( void ) mk_shell_handle ( &g_mkShellApplication.shell, &l_message );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }
   }

   /* Une erreur critique vient de se produire */
   /* Fermeture de l'application */
   ( void ) mk_shellApplication_delete ( &g_mkShellApplication );

   /* Fermeture de l'application */
   ( void ) mk_application_close ( l_application, K_MK_NULL );

   /* Boucle pour toujours */
   while ( 1 )
   {
      /* Ne rien faire */
   }

   /* Retour */
   return;
}


