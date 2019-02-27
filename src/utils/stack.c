/*
 * Copyright (C) 2019 Alexandros Theodotou <alex at zrythm dot org>
 *
 * This file is part of Zrythm
 *
 * Zrythm is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Zrythm is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Zrythm.  If not, see <https://www.gnu.org/licenses/>.
 */

/**
 * \file
 *
 * Stack implementation.
 */

#include "utils/stack.h"

int
stack_size (Stack * s)
{
  return s->top + 1;
}

int
stack_is_empty (Stack * s)
{
  return stack_size (s) == 0;
}

int
stack_is_full (Stack * s)
{
  return stack_size (s) == s->max_length;
}

Stack *
stack_new (int length)
{
  Stack * self = calloc (1, sizeof (Stack));

  self->elements = calloc (length, sizeof (void *));
  self->max_length = length;

  return self;
}

void *
stack_peek (Stack * s)
{
  if (!stack_is_empty (s))
    return s->elements[s->top];

  g_warning ("Stack is empty");
  return NULL;
}

void
stack_push (Stack *    s,
            void *     element)
{
  if (stack_is_full (s))
    g_warning ("stack is full, cannot push");
  else
    {
      s->elements[++s->top] = element;
    }
}

void *
stack_pop (Stack * s)
{
  if (stack_is_empty (s))
    {
      g_error ("Can't pop, stack is empty");
    }
  else
    {
      return s->elements[s->top--];
    }
}

/**
 * Pops the last element and moves everything back.
 */
void *
stack_pop_last (Stack * s)
{
  void * element = s->elements[0];

  for (int i = 0; i < s->max_length - 1; i++)
    {
      s->elements[i] = s->elements[i + 1];
    }
  s->top--;

  return element;
}
