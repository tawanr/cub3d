/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_keys.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 21:51:00 by tratanat          #+#    #+#             */
/*   Updated: 2022/08/08 22:05:26 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_KEYS_H
# define INPUT_KEYS_H

# if defined(__APPLE__) || defined(__MACH__)
#  define KEY_D 2
#  define KEY_A 0
#  define KEY_W 13
#  define KEY_S 1
#  define KEY_LEFT 123
#  define KEY_RGHT 124
#  define KEY_DOWN 125
#  define KEY_UP 126
#  define KEY_Q 12
#  define KEY_E 14
#  define KEY_ESC 53
#  define MSE_LEFT 1
#  define MSE_RIGHT 2
# else
#  define KEY_D 100
#  define KEY_A 97
#  define KEY_W 119
#  define KEY_S 115
#  define KEY_LEFT 65361
#  define KEY_RGHT 65363
#  define KEY_DOWN 65364
#  define KEY_UP 65362
#  define KEY_Q 113
#  define KEY_E 101
#  define KEY_ESC 65307
#  define MSE_LEFT 1
#  define MSE_RIGHT 3
# endif

#endif