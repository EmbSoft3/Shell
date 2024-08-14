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
* @file mk_shellApplication.h
* @brief Déclaration des fonctions publiques dédiées à l'application 'Shell'.
* @date 4 août 2024
*
*/

#ifndef MK_SHELL_APPLICATION_H
#define MK_SHELL_APPLICATION_H

/**
 * @fn void mk_shellApplication_main ( T_mkAddr p_param );
 * @brief Cette fonction est la fonction de démarrage de l'application.
 * @param[in] p_param Ce paramètre contient l'adresse d'une application de type \ref T_mkApplication.
 *
 * @return Sans objet.
 *
 */

void mk_shellApplication_main ( T_mkAddr p_param );

/**
 * @fn T_mkCode mk_shellApplication_init ( T_mkShellApplication* p_shell, T_mkApplication* p_application );
 * @brief Cette fonction initialise une application de type \ref T_mkShellApplication.
 *
 * @param[out] p_shell       Ce paramètre contient l'adresse d'une application de type \ref T_mkShellApplication.
 * @param[in]  p_application Ce paramètre contient l'adresse d'une application de type \ref T_mkApplication.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK                  : l'initialisation de l'application a réussi.
 *         \li \ref K_MK_ERROR_PARAM         : l'initialisation de l'application a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_MALLOC        : l'initialisation de l'application a échoué car une erreur d'allocation dynamique s'est produite.
 *         \li \ref K_MK_ERROR_ISR           : l'initialisation de l'application a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_RIGHT         : l'initialisation de l'application a échoué car une tâche non privilégiée ne possède pas suffisamment de droits.
 *         \li \ref K_MK_ERROR_TIMEOUT       : l'initialisation de l'application a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM          : l'initialisation de l'application a échoué car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_CORRUPTED     : l'initialisation de l'application a échoué car une ressource est corrompue (table des clusters).
 *         \li \ref K_MK_ERROR_UNEXPECTED    : l'initialisation de l'application a échoué car une erreur inattendue s'est produite.
 *         \li \ref K_MK_ERROR_FULL          : l'initialisation de l'application a échoué car l'espace sur le disque est insuffisant.
 *         \li \ref K_MK_ERROR_COLLISION     : l'initialisation de l'application a échoué car le nombre de collisions max dans la détermination d'un nom de fichier court a été atteint.
 *         \li \ref K_MK_ERROR_WRITE_PROTECT : l'initialisation de l'application a échoué car le disque est protégé en écriture.
 *         \li \ref K_MK_ERROR_DENIED        : l'initialisation de l'application a échoué car les fichiers n'ont pas été ouvert avec les droits adéquates (écriture ou lecture).
 *
 */

T_mkCode mk_shellApplication_init ( T_mkShellApplication* p_shell, T_mkApplication* p_application );

/**
 * @fn T_mkCode mk_shellApplication_delete ( T_mkShellApplication* p_shell );
 * @brief Cette fonction détruit une application de type \ref T_mkShellApplication.
 * @param[in, out] p_shell       Ce paramètre contient l'adresse d'une application de type \ref T_mkShellApplication.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK                  : la destruction de l'application a réussi.
 *         \li \ref K_MK_ERROR_PARAM         : la destruction de l'application a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR           : la destruction de l'application a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_RIGHT         : la destruction de l'application a échoué car une tâche non privilégiée ne possède pas suffisamment de droits.
 *         \li \ref K_MK_ERROR_TIMEOUT       : la destruction de l'application a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM          : la destruction de l'application a échoué car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_UNEXPECTED    : la destruction de l'application a échoué car une erreur inattendue s'est produite.
 *
 */

T_mkCode mk_shellApplication_delete ( T_mkShellApplication* p_shell );

/**
 * @fn T_mkCode mk_shellApplication_listenApplication ( T_mkContainer* p_container, T_mkField* p_field, T_mkCtrlId p_appCtrlId, T_mkAddr p_appCtrl, T_mkCtrlEvent p_evtCtrl, uint32_t p_ctrlId );
 * @brief Cette fonction est la fonction d'écoute applicative du container de l'application. Elle est exécutée par le moteur graphique lorsqu'un événement se produit.
 *
 * @param[in] p_container Ce paramètre contient l'adresse du container propriétaire du champ p_mkField.
 * @param[in] p_field     Ce paramètre contient la valeur \ref K_MK_NULL.
 * @param[in] p_appCtrlId Ce paramètre contient l'identifiant du contrôle applicatif ayant déclenché l'événement (\ref T_mkCtrlId).
 * @param[in] p_appCtrl   Ce paramètre contient l'adresse du contrôle applicatif ayant déclenché l'événement (\ref T_mkMouse, \ref T_mkKeyboard, ...). Celui-ci peut être nul.
 * @param[in] p_evtCtrl   Ce paramètre contient le type de l'événement (\ref T_mkCtrlEvent).
 * @param[in] p_ctrlId    Ce paramètre contient l'identifiant de l'événement.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK            : l'exécution de la fonction d'écoute a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : l'exécution de la fonction d'écoute a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : l'exécution de la fonction d'écoute a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_RIGHT   : l'exécution de la fonction d'écoute a échoué car une tâche non privilégiée ne possède pas suffisamment de droits.
 *         \li \ref K_MK_ERROR_TIMEOUT : l'exécution de la fonction d'écoute a échoué car un timeout s'est produit.
 *
 */

T_mkCode mk_shellApplication_listenApplication ( T_mkContainer* p_container, T_mkField* p_field, T_mkCtrlId p_appCtrlId, T_mkAddr p_appCtrl, T_mkCtrlEvent p_evtCtrl, uint32_t p_ctrlId );

/**
 * @fn T_mkCode mk_shellApplication_listenConsole ( T_mkContainer* p_container, T_mkField* p_field, T_mkCtrlId p_appCtrlId, T_mkAddr p_appCtrl, T_mkCtrlEvent p_evtCtrl, uint32_t p_ctrlId );
 * @brief Cette fonction est la fonction d'écoute de la console de l'application. Elle est exécutée par le moteur graphique lorsqu'un événement se produit.
 *
 * @param[in] p_container Ce paramètre contient l'adresse du container propriétaire du champ p_field.
 * @param[in] p_field     Ce paramètre contient l'adresse du champ \ref T_mkField présent dans la boite d'édition de la console.
 *                        L'adresse de la boite peut être récupérée en utilisant les attributs child.
 * @param[in] p_appCtrlId Ce paramètre contient l'identifiant du contrôle applicatif ayant déclenché l'événement (\ref T_mkCtrlId).
 * @param[in] p_appCtrl   Ce paramètre contient l'adresse du contrôle applicatif ayant déclenché l'événement (\ref T_mkMouse, \ref T_mkKeyboard, ...). Celui-ci peut être nul.
 * @param[in] p_evtCtrl   Ce paramètre contient le type de l'événement (\ref T_mkCtrlEvent).
 * @param[in] p_ctrlId    Ce paramètre contient l'identifiant de l'événement.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK                  : l'exécution de la fonction d'écoute a réussi.
 *         \li \ref K_MK_ERROR_PARAM         : l'exécution de la fonction d'écoute a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_UNEXPECTED    : l'exécution de la fonction d'écoute a échoué car une erreur inattendue s'est produite.
 *         \li \ref K_MK_ERROR_TIMEOUT       : l'exécution de la fonction d'écoute a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM          : l'exécution de la fonction d'écoute a échoué car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_ISR           : l'exécution de la fonction d'écoute a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_RIGHT         : l'exécution de la fonction d'écoute a échoué car une tâche de type non privilégié ne possède pas suffisamment de droits.
 *         \li \ref K_MK_ERROR_CORRUPTED     : l'exécution de la fonction d'écoute a échoué car un fichier est corrompu (table des clusters FAT).
 *         \li \ref K_MK_ERROR_FULL          : l'exécution de la fonction d'écoute a échoué car l'espace disponible sur le disque n'est pas suffisant.
 *         \li \ref K_MK_ERROR_WRITE_PROTECT : l'exécution de la fonction d'écoute a échoué car le disque est protégé en écriture.
 *         \li \ref K_MK_ERROR_COLLISION     : l'exécution de la fonction d'écoute a échoué car le nombre de collisions max dans la détermination d'un nom de fichier court a été atteint.
 *
 */

T_mkCode mk_shellApplication_listenConsole ( T_mkContainer* p_container, T_mkField* p_field, T_mkCtrlId p_appCtrlId, T_mkAddr p_appCtrl, T_mkCtrlEvent p_evtCtrl, uint32_t p_ctrlId );

/**
 *
 */

#endif
