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
* @file mk_shellApplication_constants.h
* @brief Déclaration des constantes dédiées à l'application 'Shell'.
* @date 4 août 2024
*
*/

#ifndef MK_SHELL_APPLICATION_CONSTANTS_H
#define MK_SHELL_APPLICATION_CONSTANTS_H

/**
 * @def K_MK_SHELL_APPLICATION_STACK_SIZE
 * @brief Définition de la taille de la stack de l'application 'Shell' [en multiple de mot 32bits]. \n
 *        Cette constante peut être modifiée par l'utilisateur.
 */

#define K_MK_SHELL_APPLICATION_STACK_SIZE 1024

/**
 *
 */

/**
 * @def K_MK_SHELL_APPLICATION_CONSOLE_WINDOW_SIZE
 * @brief Définition de la taille du buffer dédié à la fenêtre d'affichage de l'application 'Shell' [en octets].
 */

#define K_MK_SHELL_APPLICATION_CONSOLE_WINDOW_SIZE 16384

/**
 * @def K_MK_SHELL_APPLICATION_CONSOLE_PROMPT_SIZE
 * @brief Définition de la taille du buffer dédié à la boite de saisie de l'application 'Shell' [en octets].
 */

#define K_MK_SHELL_APPLICATION_CONSOLE_PROMPT_SIZE 16384

/**
 *
 */

/**
 *
 */

/**
 * @def K_MK_SHELL_APPLICATION_CONSOLE_WINDOW_X
 * @brief Définition de la position X de la fenêtre de la console.
 */

#define K_MK_SHELL_APPLICATION_CONSOLE_WINDOW_X 5

/**
 * @def K_MK_SHELL_APPLICATION_CONSOLE_WINDOW_Y
 * @brief Définition de la position Y de la fenêtre de la console.
 */

#define K_MK_SHELL_APPLICATION_CONSOLE_WINDOW_Y 5

/**
 * @def K_MK_SHELL_APPLICATION_CONSOLE_WINDOW_WIDTH
 * @brief Définition de la largeur de la fenêtre de la console.
 */

#define K_MK_SHELL_APPLICATION_CONSOLE_WINDOW_WIDTH ( mk_display_getWidth ( ) - ( 2 * K_MK_SHELL_APPLICATION_CONSOLE_WINDOW_X ) - 1 )

/**
 * @def K_MK_SHELL_APPLICATION_CONSOLE_WINDOW_HEIGHT
 * @brief Définition de la hauteur de la fenêtre de la console.
 */

#define K_MK_SHELL_APPLICATION_CONSOLE_WINDOW_HEIGHT ( mk_display_getHeight ( ) - ( 2 * K_MK_SHELL_APPLICATION_CONSOLE_WINDOW_Y ) - 35 )

/**
 * @def K_MK_SHELL_APPLICATION_CONSOLE_CACHE_SIZE
 * @brief Définition de la taille du cache de la console.
 */

#define K_MK_SHELL_APPLICATION_CONSOLE_CACHE_SIZE ( 4 * K_MK_SHELL_APPLICATION_CONSOLE_WINDOW_WIDTH * K_MK_SHELL_APPLICATION_CONSOLE_WINDOW_HEIGHT )

/**
 *
 */

/**
 * @def K_MK_SHELL_APPLICATION_CONSOLE_PROMPT_X
 * @brief Définition de la position X du prompt de la console.
 */

#define K_MK_SHELL_APPLICATION_CONSOLE_PROMPT_X 5

/**
 * @def K_MK_SHELL_APPLICATION_CONSOLE_PROMPT_Y
 * @brief Définition de la position Y du prompt de la console.
 */

#define K_MK_SHELL_APPLICATION_CONSOLE_PROMPT_Y ( ( float32_t ) ( uint32_t )  mk_display_getHeight ( ) - 34.0f )

/**
 * @def K_MK_SHELL_APPLICATION_CONSOLE_PROMPT_WIDTH
 * @brief Définition de la largeur du prompt de la console.
 */

#define K_MK_SHELL_APPLICATION_CONSOLE_PROMPT_WIDTH ( mk_display_getWidth ( ) - ( 2 * K_MK_SHELL_APPLICATION_CONSOLE_WINDOW_X ) - 1 )

/**
 * @def K_MK_SHELL_APPLICATION_CONSOLE_PROMPT_HEIGHT
 * @brief Définition de la hauteur du prompt de la console.
 */

#define K_MK_SHELL_APPLICATION_CONSOLE_PROMPT_HEIGHT 30


/**
 *
 */

#endif


