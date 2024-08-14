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
* @file mk_shellApplication_listenApplication.c
* @brief Définition de la fonction mk_shellApplication_listenApplication.
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

static T_mkCode mk_shellApplication_handleApplicationInputs ( T_mkShellApplication* p_shell, T_mkApplication* p_application, T_mkCtrlEvent p_evtCtrl )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Si une application a été redémarrée */
   if ( p_evtCtrl == K_MK_EVENT_RESUME )
   {
      /* Si l'application redémarrée est l'application 'Shell' */
      if ( p_application == p_shell->application )
      {
         /* Configuration de la visibilité et de l'activité de l'application */
         mk_container_setVisibility ( p_shell->container, K_MK_FIELD_VISIBLE );
         mk_container_setActivity ( p_shell->container, K_MK_FIELD_ACTIF );

         /* Focus automatique de la console */
         mk_console_setFocus ( &p_shell->console, K_MK_FIELD_STATE_FOCUS );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }
   }

   /* Sinon si une application a été suspendue */
   else if ( p_evtCtrl == K_MK_EVENT_SUSPEND )
   {
      /* Si l'application mise en pause est l'application 'Shell' */
      if ( p_application == p_shell->application )
      {
         /* Configuration de la visibilité de l'application */
         mk_container_setVisibility ( p_shell->container, K_MK_FIELD_INVISIBLE );
         mk_container_setActivity ( p_shell->container, K_MK_FIELD_INACTIF );

         /* Désactivation du focus */
         mk_console_setFocus ( &p_shell->console, K_MK_FIELD_STATE_IDLE );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }
   }

   /* Sinon si une application a été fermée ou désinstallée */
   else if ( ( p_evtCtrl == K_MK_EVENT_CLOSE ) || ( p_evtCtrl == K_MK_EVENT_UNINSTALL ) )
   {
      /* Si l'application  est l'application 'Shell' */
      if ( p_application == p_shell->application )
      {
         /* L'application et les objets graphiques sont supprimées par le gestionnaire d'applications. */
         /* On se contente de détruire la console et désallouer la boite de messages */
         l_result = mk_shellApplication_delete ( p_shell );
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

T_mkCode mk_shellApplication_listenApplication ( T_mkContainer* p_container, T_mkField* p_field, T_mkCtrlId p_appCtrlId, T_mkAddr p_appCtrl, T_mkCtrlEvent p_evtCtrl, uint32_t p_ctrlId )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Récupération de l'adresse de l'application propriétaire du container */
   T_mkApplication* l_application = mk_container_getOwner ( p_container );

   /* Si le message est à destination de l'application */
   if ( p_appCtrl == l_application )
   {
      /* Si un évènement système s'est produit */
      if ( p_appCtrlId == K_MK_CONTROL_SYSTEM )
      {
         /* Ne rien faire */
      }

      /* Sinon si un évènement en relation avec les applications s'est produit */
      else if ( p_appCtrlId == K_MK_CONTROL_APPLICATION )
      {
         /* Gestion des événéments relatifs aux applications */
         l_result = mk_shellApplication_handleApplicationInputs ( &g_mkShellApplication, p_appCtrl, p_evtCtrl );
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

   /* Suppression warning */
   ( void ) p_field; ( void ) p_appCtrlId; ( void ) p_ctrlId;

   /* Retour */
   return ( l_result );
}

