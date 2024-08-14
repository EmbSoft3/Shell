/**
*
* @copyright Mk - Copyright (C) 2017-2018 RENARD Mathieu.
*
* This file is part of Mk.
*
* Mk is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Mk is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with Mk.  If not, see <https://www.gnu.org/licenses/>.
*
* @file mk_shellApplication_types.h
* @brief Déclaration des types dédiés à l'application 'Shell'.
* @date 4 août 2024
*
*/

#ifndef MK_SHELL_APPLICATION_APPS_TYPES_H
#define MK_SHELL_APPLICATION_APPS_TYPES_H

/**
 * @struct T_mkShellConsoleMemory
 * @brief Déclaration de la structure T_mkShellConsoleMemory.
 *
 */

typedef struct T_mkShellConsoleMemory T_mkShellConsoleMemory;
struct T_mkShellConsoleMemory
{
   T_mkAddr windowCache;                                                /*!< Ce membre contient l'adresse du cache dédié à la fenêtre de la console. */
   T_mkAddr promptCache;                                                /*!< Ce membre contient l'adresse du cache dédié à la boite de saisie de la console. */
   T_mkAddr windowAddr;                                                 /*!< Ce membre contient l'adresse du buffer stockant les caractères de la fenêtre de la console. */
   T_mkAddr promptAddr;                                                 /*!< Ce membre contient l'adresse du buffer stockant les caractères de la boite d'édition de la console. */
};


/**
 * @struct T_mkShellApplication
 * @brief Déclaration de la structure T_mkShellApplication.
 *
 */

typedef struct T_mkShellApplication T_mkShellApplication;
struct T_mkShellApplication
{
   T_mkApplication* application;                                        /*!< Ce membre contient l'adresse de l'application. */
   T_mkShell shell;                                                     /*!< Ce membre contient le gestionnaire de commande de l'application. */
   T_mkShellConsoleMemory memory;                                       /*!< Ce membre contient les données relatives à mémoire de la console. */
   T_mkContainer* container;                                            /*!< Ce membre contient le container de l'application. */
   T_mkLayer layer;                                                     /*!< Ce membre contient l'objet de configuration des layers de l'application. */
   T_mkConsole console;                                                 /*!< Ce membre contient la console de l'application. */
};

/**
 *
 */

#endif

