/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 10:42:27 by coremart          #+#    #+#             */
/*   Updated: 2019/09/09 04:28:59 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

#include <limits.h>

#include <stdio.h>

# define FLOW 2
# define NO_FLOW 1
# define EDGE 0x3
# define STDIN 0
# define SAME 0

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

typedef struct	s_parser_graph
{
int				**matrix;
int				*adj_edges_count;
t_source_end	commands;
t_vertex_list	*start;
t_vertex_list	*end;
int				ants;
}				t_parser_graph;

/*
**	parser.c
*/
t_parser_graph		*parser(void);

/*
**	vertices_utils.c
*/
t_parser_graph	*pars_vertices(void);
int				get_vertex(char *str, t_vertex_list *start);
void			add_comment(char line[]);
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

#endif
