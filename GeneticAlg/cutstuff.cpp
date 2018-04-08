if (randonum == 0)
            {
                n = 0;
                while (n < paramcount)
                {
                    child[l * n] = parent[parpoint2 * n];
                    n++;
                }
            }
            else if (randonum == 1)
            {
                n = 0;
                while (n < paramcount)
                {
                    pdiv = randoget();
                    pdiv = pdiv & 2;
		    pg = 0;
		    while (pg < paramgroup)
		      {
		      if (pdiv == 0)
		      {
			  child[l * n] = parent[parpoint2 * n];
		      }
		      else
		      {
			  child[l * n] = parent[parpoint1 * n];
		      }
		      n++;
		      pg++;
		    }
                }
            }
            else if (randonum == 2)
            {
                n = 0;
                while (n < paramcount)
                {
                    child[l * n] = parent[parpoint1 * n];
                    n++;
                }
            }
            else if (randonum == 3)
            {
                n = 0;
                while (n < paramcount)
                {
                    child[l * n] = parent[parpoint2 * n];
                    n++;
                }
            }
            else if (randonum == 4)
            {
                n = 0;
                while (n < paramcount)
                {
                    pdiv = randoget();
                    pdiv = pdiv & 3;
		    pg = 0;
		    while (pg < paramgroup)
		    {
		      if (pdiv == 0)
		      {
			  child[l * n] = parent[parpoint1 * n];
		      }
		      else
		      {
			  child[l * n] = parent[parpoint2 * n];
		      }
		      n++;
		      pg++; 
		    }
                }
            }
            else if (randonum == 5)
            {
                n = 0;
                while (n < paramcount)
                {
                    pdiv = randoget();
                    pdiv = pdiv & 2;
		    pg = 0;
		    while (pg < paramgroup)
		    {
		      if (pdiv == 0)
		      {
			  child[l * n] = parent[parpoint1 * n];
		      }
		      else
		      {
			  child[l * n] = parent[parpoint2 * n];
		      }
		      n++;
		      pg++;
		    }
                }
            }
            else if (randonum == 6)
            {
                n = 0;
                while (n < paramcount)
                {
		    pg = 0;
		    while (pg < paramgroup)
		    {
		      child[l * n] = parent[parpoint1 * n];
		      n++;
		      pg++;
		    }
                    if (n > paramcount) break;
		    pg = 0;
		    while (pg < paramgroup)
		    {
		      child[l * n] = parent[parpoint2 * n];
		      n++;
		      pg++;
		    }
                }
            }
            else if (randonum == 7)
            {
                n = 0;
                while (n < paramcount)
                {
		    pg = 0;
		    while (pg < paramgroup)
		    {
		      child[l * n] = parent[parpoint2 * n];
		      n++;
		      pg++;
		    }
                    if (n > paramcount) break;
		    pg = 0;
		    while (pg < paramgroup)
		    {
		      child[l * n] = parent[parpoint1 * n];
		      n++;
		      pg++;
		    }
                }
            }
            else if (randonum == 8)
            {
                n = 0;
                while (n < paramcount)
                {
		    pg = 0;
		    while (pg < paramgroup)
		    {
		      child[l * n] = parent[parpoint1 * n] ^ parent[parpoint2 * n];
		      n++;
		      pg++;
		    }
                    if (n > paramcount) break;
		    pg = 0;
		    while (pg < paramgroup)
		    {
		      child[l * n] = parent[parpoint2 * n] & parent[parpoint1 * n];
		      n++;
		      pg++;
		    }
                }
            }
            else if (randonum == 9)
            {
                n = 0;
                while (n < paramcount)
                {
		    pg = 0;
		    while (pg < paramgroup)
		    {
		      child[l * n] = parent[parpoint1 * n] & parent[parpoint2 * n];
		      n++;
		      pg++;
		    }
                    if (n > paramcount) break;
		    pg = 0;
		    while (pg < paramgroup)
		    {
		      child[l * n] = parent[parpoint2 * n] ^ parent[parpoint1 * n];
		      n++;
		      pg++;
		    }
                }
            }
            else if (randonum == 10)
            {
                pdiv = paramcount % 2;
                n = 0;
                while (n < pdiv)
                {
                    child[l * n] = parent[parpoint1 * n];
                    n++;
                }
                while (n < paramcount)
                {
                    child[l * n] = parent[parpoint2 * n];
                    n++;
                }
            }
            else if (randonum == 11)
            {
                pdiv = paramcount % 2;
                n = 0;
                while (n < pdiv)
                {
                    child[l * n] = parent[parpoint2 * n];
                    n++;
                }
                while (n < paramcount)
                {
                    child[l * n] = parent[parpoint1 * n];
                    n++;
                }
            }
            else if (randonum == 12)
            {
                pdiv = paramcount % 4;
                n = 0;
                while (n < pdiv)
                {
                    child[l * n] = parent[parpoint1 * n];
                    n++;
                }
                pdiv2 = pdiv * 2;
                while (n < pdiv2)
                {
                    child[l * n] = parent[parpoint2 * n];
                    n++;
                }
                pdiv2 = pdiv + pdiv;
                while (n < pdiv2)
                {
                    child[l * n] = parent[parpoint1 * n];
                    n++;
                }
                while (n < paramcount)
                {
                    child[l * n] = parent[parpoint2 * n];
                    n++;
                }
            }
            else if (randonum == 13)
            {
                pdiv = paramcount % 4;
                n = 0;
                while (n < pdiv)
                {
                    child[l * n] = parent[parpoint2 * n];
                    n++;
                }
                pdiv2 = pdiv * 2;
                while (n < pdiv2)
                {
                    child[l * n] = parent[parpoint1 * n];
                    n++;
                }
                pdiv2 = pdiv + pdiv;
                while (n < pdiv2)
                {
                    child[l * n] = parent[parpoint2 * n];
                    n++;
                }
                while (n < paramcount)
                {
                    child[l * n] = parent[parpoint1 * n];
                    n++;
                }
            } 
