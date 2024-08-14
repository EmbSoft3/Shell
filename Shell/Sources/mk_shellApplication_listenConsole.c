/**
*
* @copyright Copyright (C) 2024 RENARD Mathieu. All rights reserved.
*
* This file is part of mk.
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
* @file mk_shellApplication_listenConsole.c
* @brief Définition de la fonction mk_shellApplication_listenConsole.
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
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_shellApplication_getInputFileName ( T_str8 p_randomFileName )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une variable de retour locale */
   int32_t l_ret = 0;

   /* Déclaration d'un compteur */
   uint32_t l_counter = 0;

   /* Déclaration d'un ensemble de variable contenant les nombres aléatoires et leurs conversions en ASCII */
   uint32_t l_randNumber [ 2 ] = { 0, 0 };
   char8_t  l_randString [ 2 ] [ 9 ] = { { 0 } };

   /* Création de la base de la chaine de caractères */
   ( void ) mk_utils_strcat ( ( T_str8 ) p_randomFileName, ( T_str8 ) p_randomFileName, K_MK_SHELL_PATH );

   /* Pour le nombre de données aléatoires à générer */
   for ( l_counter = 0 ; ( l_counter < 2 ) && ( l_ret != ( -2 ) ) ; l_counter++ )
   {
      /* Effectue */
      do
      {
         /* Récupération d'un nombre aléatoire */
         l_ret = mk_utils_rand ( &l_randNumber [ l_counter ] );

      /* Tant que la conversion n'est pas terminée et tant qu'aucune erreur ne s'est produite */
      } while ( l_ret == ( -3 ) );
   }

   /* Si aucune erreur ne s'est produite */
   if ( l_ret == 0 )
   {
      /* Conversion des nombres aléatoires en chaine de caractères */
      ( void ) mk_utils_itoa ( ( uint32_t ) l_randNumber [ 0 ], ( T_str8 ) &l_randString [ 0 ] [ 0 ], 16, 8 );
      ( void ) mk_utils_itoa ( l_randNumber [ 1 ], ( T_str8 ) &l_randString [ 1 ] [ 0 ], 16, 8 );

      /* Concaténéation des nombres aléatoires dans la chaine */
      ( void ) mk_utils_strcat ( ( T_str8 ) p_randomFileName, ( T_str8 ) p_randomFileName, ( T_str8 ) &l_randString [ 0 ] [ 0 ] );
      ( void ) mk_utils_strcat ( ( T_str8 ) p_randomFileName, ( T_str8 ) p_randomFileName, ( T_str8 ) &l_randString [ 1 ] [ 0 ] );
      ( void ) mk_utils_strcat ( ( T_str8 ) p_randomFileName, ( T_str8 ) p_randomFileName, ( T_str8 ) ".input" );
   }

   /* Sinon */
   else
   {
      /* Actualisation de la variable de retour */
      l_result = K_MK_ERROR_UNEXPECTED;
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_shellApplication_shareFile ( T_mkConsole* p_console, T_mkEditField* p_editField )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'une variable de retour intermédiaire */
   T_mkCode l_ret = K_MK_ERROR_PARAM;

   /* Déclaration d'une variable stockant la longueur de la chaine de caractères */
   uint32_t l_numberOfBytesToWrite = 0, l_numberOfBytesWrite = 0;

   /* Déclaration d'un message à destination du gestionnaire de commandes */
   T_mkShellMessage l_message =  { { 0 }, p_console };

   /* Déclaration d'un pointeur de fichiers */
   T_mkFile* l_file = K_MK_NULL;

   /* Effectue */
   do
   {
      /* Récupération d'un nom de fichier aléatoire */
      l_result = mk_shellApplication_getInputFileName ( ( T_str8 ) l_message.fileName );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Test de l'existance du fichier à créer */
         l_ret = mk_file_stat ( K_MK_NULL, ( T_str8 ) l_message.fileName, K_MK_NULL );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

   /* Tant qu'un nom unique n'a pas été trouvé et tant qu'aucune erreur ne s'est produite */
   } while ( ( l_ret == K_MK_OK ) && ( l_result == K_MK_OK ) );

   /* Si aucune erreur ne s'est produite */
   if ( ( l_result == K_MK_OK ) && ( l_ret == K_MK_ERROR_NOT_FOUND ) )
   {
      /* Création du fichier stockant la chaine de caractères saisie par l'utilisateur */
      l_result = mk_file_open ( K_MK_NULL, &l_file, ( T_str8 ) l_message.fileName, K_MK_FS_OPEN_ALWAYS | K_MK_FS_OPEN_READ | K_MK_FS_OPEN_WRITE, K_MK_NULL );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Récupération de la longueur de la chaine de caractères */
         /* Pas besoin de protection car la chaine de caractères est issue du prompt (pas d'accès concurrent) */
         l_numberOfBytesToWrite = mk_utils_utfsize ( ( T_str8 ) p_editField->strAddr, p_console->foreground.window.style.fontEncoding );
         l_numberOfBytesToWrite += mk_utils_utfnull ( p_console->foreground.window.style.fontEncoding );

         /* Ecriture de la chaine dans le fichier */
         l_result = mk_file_write ( l_file, p_editField->strAddr, l_numberOfBytesToWrite, &l_numberOfBytesWrite, K_MK_NULL );

         /* Si une erreur d'écriture s'est produite */
         if ( ( l_result == K_MK_OK ) && ( l_numberOfBytesToWrite != l_numberOfBytesWrite ) )
         {
            /* Actualisation de la variable de retour */
            l_result = K_MK_ERROR_UNEXPECTED;
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Fermeture du fichier (sans condition) */
         l_result |= mk_file_close ( l_file, K_MK_NULL );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Transmission d'un message à la tâche de gestion des messages */
         l_result = mk_mail_post ( g_mkShellApplicationMessageArea.mail, ( T_mkAddr ) &l_message, K_MK_STATE_READY, 0 );

         /* Si une erreur s'est produite */
         if ( l_result == K_MK_ERROR_TIMEOUT )
         {
            /* Affichage de la commande dans la console */
            l_result = mk_console_log ( p_console, p_editField->strAddr );

            /* Si aucune erreur ne s'est produite */
            if ( l_result == K_MK_OK )
            {
               /* Affichage d'un message d'erreur dans la console */
               l_result = mk_console_log ( p_console, ( T_str8 ) "Failed to process command. Retry later." );
            }

            /* Sinon */
            else
            {
               /* Ne rien faire */
            }
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }
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

T_mkCode mk_shellApplication_listenConsole ( T_mkContainer* p_container, T_mkField* p_field, T_mkCtrlId p_appCtrlId, T_mkAddr p_appCtrl, T_mkCtrlEvent p_evtCtrl, uint32_t p_ctrlId )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Récupération de l'adresse de la boite d'édition */
   T_mkEditField* l_editField = ( T_mkEditField* ) p_field->child;

   /* Récupération de l'adresse de la console */
   T_mkConsole* l_console = ( T_mkConsole* ) l_editField->child;

   /* Si un événement en relation avec le clavier s'est produit */
   if ( p_appCtrlId == K_MK_CONTROL_KEYBOARD )
   {
      /* Si l'utilisateur a saisi une commande */
      if ( ( p_field->focus == K_MK_FIELD_STATE_FOCUS ) && ( p_evtCtrl == K_MK_EVENT_KEY_DOWN ) && ( p_ctrlId == K_MK_KEYBOARD_ENTER ) )
      {
         /* Enregistrement de la commande dans un fichier de partage et */
         /* transmission d'un message à la tâche de gestion des commandes. */
         l_result = mk_shellApplication_shareFile ( l_console, l_editField );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Exécution du listener par défaut de la console */
      l_result = mk_console_defaultListener ( p_container, p_field, p_appCtrlId, p_appCtrl, p_evtCtrl, p_ctrlId );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return ( l_result );
}


