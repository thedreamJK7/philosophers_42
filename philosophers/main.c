/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 12:07:43 by jkubaev           #+#    #+#             */
/*   Updated: 2025/11/10 15:38:40 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

/*
** Main function to start the philosophers simulation.
** It initializes the data, starts the philosopher routines, and cleans up resources.
*/

int	main(int argc, char	**argv)
{
	t_data	data;

	if (init_data(&data, argc, argv) != 0)
		return (1);
	
}
