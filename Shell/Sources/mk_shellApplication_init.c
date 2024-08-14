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
* @file mk_shellApplication_init.c
* @brief Déclaration de la fonction mk_shellApplication_init.
* @date 4 août 2024
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

static void mk_shellApplication_getFileName ( T_mkShellApplication* p_shell, T_str8 p_str, T_str8 p_suffix )
{
   /* Déclaration d'une variable contenant le TID de la tâche courante */
   char8_t l_tid [ 11 ] = { 0 };

   /* Conversion du TID de la tâche de l'application en ASCII */
   ( void ) mk_utils_itoa ( p_shell->application->task.addr->attribute.identifier, ( T_str8 ) l_tid, 10, 0 );

   /* Création de la chaine de caractères */
   ( void ) mk_utils_strcat ( ( T_str8 ) p_str, ( T_str8 ) K_MK_SHELL_PATH, ( T_str8 ) "TID_" );
   ( void ) mk_utils_strcat ( ( T_str8 ) p_str, ( T_str8 ) p_str, ( T_str8 ) l_tid );
   ( void ) mk_utils_strcat ( ( T_str8 ) p_str, ( T_str8 ) p_str, ( T_str8 ) p_suffix );

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_shellApplication_open ( T_mkShellApplication* p_shell )
{
   /* Déclaration de la variable dmk_shellApplication_opene retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration des variables contenant les noms des fichiers d'entrées et de sorties */
   char8_t l_strIn [ 48 ] = { 0 }, l_strOut [ 48 ] = { 0 };

   /* Création du nom de fichier de sortie */
   mk_shellApplication_getFileName ( p_shell, ( T_str8 ) l_strOut, ( T_str8 ) "h_stdout.log" );

   /* Création du nom de fichier d'entrée */
   mk_shellApplication_getFileName ( p_shell, ( T_str8 ) l_strIn, ( T_str8 ) "h_stdin.log" );

   /* Ouverture de la console */
   l_result = mk_console_open ( &p_shell->console, K_MK_NULL, ( T_str8 ) l_strIn, ( T_str8 ) l_strOut );

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_shellApplication_initMessagePool ( void )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Initialisation de la zone mémoire dédiées à la messagerie */
   l_result = mk_pool_initArea ( &g_mkShellApplicationMessageArea.area,
                                  g_mkShellApplicationMessageArea.heap, K_MK_SHELL_INCOMING_MESSAGE_AREA_SIZE );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Initialisation de la messagerie */
      l_result = mk_mail_create ( &g_mkShellApplicationMessageArea.mail, K_MK_AREA_PROTECTED,
                                  &g_mkShellApplicationMessageArea.area, K_MK_SHELL_INCOMING_MESSAGE_SIZE, K_MK_SHELL_MESSAGE_NUMBER );
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

static void mk_shellApplication_initMemory ( T_mkShellApplication* p_shell, T_mkApplication* p_application )
{
   /* Configuration des pointeurs mémoires */
   /* Attention à la taille de la page mémoire */
   /* Taille = 1 228 800 octets */
   /* Taille cache = 1 096 976 */
   /* Taille buffer fenêtre : 16384 */
   /* Taille buffer prompt : 16384 */
   /* Reste : 99 056 octets */
   p_shell->memory.promptCache = K_MK_NULL;
   p_shell->memory.windowCache = ( uint8_t* ) p_application->page.gfxAddr;
   p_shell->memory.windowAddr = ( uint8_t* ) p_shell->memory.windowCache + K_MK_SHELL_APPLICATION_CONSOLE_CACHE_SIZE;
   p_shell->memory.promptAddr = ( uint8_t* ) p_shell->memory.windowAddr + K_MK_SHELL_APPLICATION_CONSOLE_WINDOW_SIZE;

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_shellApplication_setAttributes ( T_mkShellApplication* p_shell )
{
   /* Déclaration de la structure de configuration des attributs de l'application */
   T_mkDispatcherAttributes l_attributes = {
         K_MK_POINTER_DEFAULT_RESOLUTION,          /* Résolution des curseurs. */
         K_MK_STICK_DEFAULT_RESOLUTION,            /* Résolution des sticks. */
         K_MK_GRAPHICS_FOREGROUND,                 /* Layer du curseur de la souris. */
         K_MK_FIELD_VISIBLE,                       /* Visiblité du curseur de la souris. */
         K_MK_NULL,                                /* Curseur par défaut. */
         0, 0,                                     /* Largeur et hauteur du curseur (non utilisé si curseur par défaut). */
         K_MK_KEYBOARD_HOLD_INHIBITION_DURATION,   /* Durée entre un événement 'Down' et 'Hold'. */
         K_MK_KEYBOARD_HOLD_RATE                   /* Durée entre deux événements 'Hold'. */
   };

   /* Configuration des attributs de l'application */
   T_mkCode l_result = mk_application_setAttributes ( p_shell->application, &l_attributes, K_MK_NULL );

   /* Retour */
   return ( l_result );
}


/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_shellApplication_setContainer ( T_mkShellApplication* p_shell )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Initialisation d'un container */
   l_result = mk_container_create ( &p_shell->container, mk_shellApplication_listenApplication, K_MK_NULL );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Ajout des champs dans le container */
      l_result  = mk_container_addField ( p_shell->container, &p_shell->layer.field, K_MK_NULL );
      l_result |= mk_console_addContainer ( &p_shell->console, p_shell->container );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Ajout du container dans la factory */
      l_result = mk_factory_addContainer ( p_shell->container, K_MK_NULL );
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

T_mkCode mk_shellApplication_init ( T_mkShellApplication* p_shell, T_mkApplication* p_application )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Enregistrement de l'adresse de l'application */
   p_shell->application = p_application;

   /* Initialisation des attributs mémoire de l'application */
   mk_shellApplication_initMemory ( p_shell, p_application );

   /* Initialisation des layers */
   mk_layer_init ( &p_shell->layer );
   mk_layer_set ( &p_shell->layer, K_MK_LAYER_FOREGROUND_VISIBLE );
   mk_layer_setAlpha ( &p_shell->layer, 255, 255 );

   /* Initialisation de la console */
   mk_console_init ( &p_shell->console, p_shell->memory.promptAddr, K_MK_SHELL_APPLICATION_CONSOLE_PROMPT_SIZE,
                      p_shell->memory.windowAddr, K_MK_SHELL_APPLICATION_CONSOLE_WINDOW_SIZE );
   mk_console_setLocalEcho ( &p_shell->console, K_MK_CONSOLE_LOCALECHO_DISABLED );
   mk_console_setPosition ( &p_shell->console, K_MK_CONSOLE_WINDOW, K_MK_SHELL_APPLICATION_CONSOLE_WINDOW_X, K_MK_SHELL_APPLICATION_CONSOLE_WINDOW_Y );
   mk_console_setDimension ( &p_shell->console, K_MK_CONSOLE_WINDOW, K_MK_SHELL_APPLICATION_CONSOLE_WINDOW_WIDTH, K_MK_SHELL_APPLICATION_CONSOLE_WINDOW_HEIGHT );
   mk_console_setPosition ( &p_shell->console, K_MK_CONSOLE_PROMPT, K_MK_SHELL_APPLICATION_CONSOLE_PROMPT_X, K_MK_SHELL_APPLICATION_CONSOLE_PROMPT_Y );
   mk_console_setDimension ( &p_shell->console, K_MK_CONSOLE_PROMPT, K_MK_SHELL_APPLICATION_CONSOLE_PROMPT_WIDTH, K_MK_SHELL_APPLICATION_CONSOLE_PROMPT_HEIGHT );
   mk_console_setCache ( &p_shell->console, K_MK_CONSOLE_WINDOW, p_shell->memory.windowCache );
   mk_console_setCache ( &p_shell->console, K_MK_CONSOLE_PROMPT, p_shell->memory.promptCache );
   mk_console_setBackgroundColor ( &p_shell->console, K_MK_CONSOLE_WINDOW, K_MK_COLOR_ARGB_BLACK );
   mk_console_setBackgroundColor ( &p_shell->console, K_MK_CONSOLE_PROMPT, K_MK_COLOR_ARGB_BLACK );
   mk_console_setBackgroundColor ( &p_shell->console, K_MK_CONSOLE_SCREEN, K_MK_COLOR_ARGB_BLACK );
   mk_console_setVisibility ( &p_shell->console, K_MK_FIELD_VISIBLE );
   mk_console_setActivity ( &p_shell->console, K_MK_FIELD_ACTIF );
   mk_console_setFocus ( &p_shell->console, K_MK_FIELD_STATE_FOCUS );
   mk_console_setListener ( &p_shell->console, mk_shellApplication_listenConsole );

   /* On s'assure que la console est bien en UTF8 */
   mk_console_setTextEncoding ( &p_shell->console, K_MK_FONT_UTF8 );
   mk_console_setTextColor ( &p_shell->console, K_MK_COLOR_ARGB_ORANGE );

   /* Initialisation de la messagerie */
   l_result = mk_shellApplication_initMessagePool ( );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Initialisation des attributs des périphériques (clavier, souris, ...) */
      l_result = mk_shellApplication_setAttributes ( p_shell );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Initialisation du gestionnaire de commandes */
      l_result = mk_shell_init ( &p_shell->shell );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Ouverture de la console */
      l_result = mk_shellApplication_open ( p_shell );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Configuration du container de l'application */
      l_result = mk_shellApplication_setContainer ( p_shell );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return ( l_result );
}


