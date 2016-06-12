/*nptr insert( nptr x, nptr root)
  {	x->colour=r;
  while(x!=root && x->prev->colour==r)
  {	if(x->prev=x->prev->prev->left)
  {	nptr y=x->prev->prev->right;//check again
  if(y->colour==r)
  {	x->prev->colour=b;
  y->colour=b;
  x->prev->prev->colour=r;
  x=x->prev->prev;//check again
  }
  else if(x=x->prev->right)
  {	x=x->prev;
  lr(x);
  x->prev->colour=b;
  x->prev->prev->colour=r;
  rr(x->prev->prev);
  }
  }
  else
  {	nptr y=x->prev->prev->left;//check 
  if(y->colour==r)
  {       x->prev->colour=b;
  y->colour=b;
  x->prev->prev->colour=r;
  x=x->prev->prev;//check again
  }
  else if(x=x->prev->left)
  {       x=x->prev;
  lr(x);
  x->prev->colour=b;
  x->prev->prev->colour=r;
  rr(x->prev->prev);
  }
  }
  root->colour=b;
  }
  return root;
  }""*/
