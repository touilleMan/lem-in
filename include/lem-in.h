/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 10:42:27 by coremart          #+#    #+#             */
/*   Updated: 2019/09/11 14:33:04 by cbenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

#include <limits.h>
#include <stdio.h>
#include "../libft/include/libft.h"
#include "stdlib.h"
#include "stdio.h"
#include "unistd.h"

# define FLOW 2
# define NO_FLOW 1
# define EDGE 0x3
# define STDIN 0
# define SAME 0
# define LEM_IN_BUFF_SIZE 2048
# define SUCCESS 0
# define FAILURE 1

# define BONUS_C 0
# define BONUS_V 1
# define BONUS_N 2
# define BONUS_P 3
# define BONUS_D 4
# define BONUS_M 5
# define COLOR_RESET "\033[0m"
# define COLOR_V "\033[1;31m"
# define COLOR_N "\033[1;31m"
# define COLOR_P "\033[1;31m"
# define COLOR_D "\033[1;31m"
# define COLOR_M "\033[1;31m"

void	print_matrix(int **matrix, int size);


typedef struct	s_source_end
{
	int	s;
	int	t;
}				t_source_end;

typedef struct	s_graph
{
	int				*flow_arr; //0:no flow, 1:flow, 2:blocking flow
	int				*adj_edges_arr;
	int				*level_arr;
	int				**adj_matrix;
	int				size;
	int				ants;
	t_source_end	s_t;
}				t_graph;

typedef struct	s_queue
{
	int				value;
	struct s_queue	*next;
}				t_queue;

typedef struct	s_queue_ptr
{
	t_queue	*start;
	t_queue	*end;
}				t_queue_ptr;

typedef struct	s_path
{
	int	*path;
	int	len;
	int	ants_on;
}				t_path;

typedef struct	s_paths
{
	t_path			*paths;
	int	size;
}				t_paths;

typedef struct	s_parser_vertex
{
	char*	name;
	int		nb;
}				t_parser_vertex;

typedef struct	s_vertex_list
{
	t_parser_vertex			vertex;
	struct s_vertex_list	*next;
}				t_vertex_list;

typedef struct	s_parsing_list
{
	char					*line;
	struct s_parsing_list	*next;
}				t_parsing_list;

typedef struct	s_parser_graph
{
	int				**matrix;
	int				*adj_edges_count;
	t_source_end	commands;
	t_vertex_list	*start;
	t_vertex_list	*end;
	int				ants;
	t_parsing_list	*parsing_list_start;
	t_parsing_list	*parsing_list_end;
	char			*msg;
	int				flag[6];
	int				nb_lines;
}				t_parser_graph;

typedef struct	s_buff_printer
{
char	buff[LEM_IN_BUFF_SIZE];
int		index;
}				t_buff_printer;


/*
**	bonus.c
*/
int				fill_option(t_parser_graph *graph, char **av);
int				set_msg(int return_value, t_parser_graph *graph, char *msg);
int				ft_break(int return_value, int n, ...);

/*
**	parser.c
*/
void			parser(t_parser_graph *graph);
t_parser_graph	*init_pars_graph(void);

/*
**	vertices_utils.c
*/
char			*pars_vertices(t_parser_graph *graph);
int				get_vertex(char *str, t_vertex_list *start);
char			*pars_name(char *line);

/*
**	list_utils.c
*/
void			add_elem(t_vertex_list **end, char line[]);
t_vertex_list	*init_list(void);

/*
**	edges_utils.c
*/
void			pars_edges(t_parser_graph *p_graph, char *line);

/*
**	get_max_flow.c
*/
t_paths				get_max_flow(t_graph *graph);
int				get_next_vertex(int *vertex_arr, int index);

/*
**	queue.c
*/
void			init_queue(t_queue_ptr *queue, int vertex);
void			enqueue(t_queue_ptr *queue, int vertex);
int				dequeue(t_queue_ptr *queue);
void			free_queue(t_queue_ptr *queue);

/*
**	paths.c
*/
t_paths	get_new_paths(t_graph *graph, int size);
void	dispatch_ants(t_paths paths, int ants);
int		is_worse_path(t_paths cur_paths,t_paths new_paths);
void	free_paths(t_paths paths);

/*
**	make_graph.c
*/
t_graph		*make_graph(t_parser_graph *p_graph);

/*
**	q_sort_paths.c
*/
void		q_sort_paths(t_paths paths);

/*
**	printer.c
*/
void	print_res(t_parser_graph *p_graph, t_paths *paths);

/*
**	parsing_list_utils.c
*/
t_parsing_list	*init_pars_list(char *line);
t_parsing_list	*add_pars_elem(t_parsing_list *end, char *line);
void			print_parsing_list(t_parsing_list *list);

/*
**	check_duplicates.c
*/
int		check_vertex_dup(t_vertex_list *list, char *last);

/*
**	error.c
*/
void	error_sys(void);
void	error_input(void);

/*
**	check_graph.c
*/
void		check_graph(t_parser_graph *graph);

#endif
