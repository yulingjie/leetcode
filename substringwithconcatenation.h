class Solution {
    bool compareWord(string::iterator ite,string::iterator end, string word)
    {
        string::iterator w_ite = word.begin();
        while(ite != end && w_ite != word.end())
        {
            if(*ite != *w_ite)
            {
                return false;
            }
            ++ite;
            ++w_ite;
        }
        if(w_ite != word.end())
        {
            return false;
        }
        return true;
    }
    void debug(vector<int> & tmp_indices, vector<string> & words)
    {
        int len = words[0].size();

        for(vector<int>::iterator ite = tmp_indices.begin(); ite != tmp_indices.end(); ++ite)
        {
            cout<<*ite<<" ";
        }
        cout<<endl;
        for(vector<int>::iterator ite = tmp_indices.begin(); ite != tmp_indices.end();)
        {
            if(*ite >= 0)
            {
                
                cout<<words[*ite]<<" "; 
                ite += len;
                
            }
            else
            {
                
                cout<<"____";
                ite ++;
            }
        }
        cout<<endl;
    }
    void debug(vector<vector<int> >& wordIndices,vector<string> & words)
    {
        for(vector<vector<int> >::iterator w_ite = wordIndices.begin();
            w_ite != wordIndices.end();
            ++w_ite)
        {
            cout<<words[w_ite- wordIndices.begin()]<<" ";
            for(vector<int>::iterator ite = w_ite->begin();ite != w_ite->end(); ++ite)
            {
                cout<<*ite<<" ";
            }
            cout<<endl;
        }
    }
    void debugNewWords(vector<string>& new_words, vector<int>& flags)
    {
        cout<<"new words: ";
        for(vector<string>::iterator ite = new_words.begin(); ite != new_words.end(); ++ite)
        {
            cout<<*ite<<" ";
        }
        cout<<endl;
        cout<<"flags : "; 
        for(vector<int>::iterator ite = flags.begin(); ite!= flags.end();++ite)
        {
            cout<<*ite<<" ";
        }
        cout<<endl;
    }
    public:
    vector<int> findSubstring(string s, vector<string>& words) {
        //s = "aaaaaaaa";
        //words = {"aa","aa","aa"};
        //s="lingmindraboofooowingdingbarrwingmonkeypoundcake";
        //words ={"fooo","barr","wing","ding","wing"};
        // s="wordgoodgoodgoodbestword";
        // words={"word","good","best","word"};
        if(words.size() <=0)return vector<int>();
        if(s.size()<=0) return vector<int>();
        vector<string> new_words;
        vector<int> flags;
        // remove duplication
        for(vector<string>::iterator i = words.begin(); i < words.end(); ++i)
        {
            int existIdx = -1;
            for(vector<string>::iterator j = new_words.begin(); j < new_words.end(); ++j) 
            {
                if(compareWord(i->begin(),i->end(), *j))
                {
                    existIdx = j-new_words.begin();
                }
            }
            if(existIdx< 0)
            {
                new_words.push_back(*i);
                flags.push_back(1);
            }
            else
            {
                flags[existIdx] ++;
            }

        }
        //debugNewWords(new_words, flags);
        int word_length = new_words[0].size();
        //int word_num = s.size()/word_length;
        vector<vector<int> > wordIndices;
        for(int i = 0; i < new_words.size(); ++i)
        {
            vector<int> vec(s.size(),-1);
            wordIndices.push_back(vec);
        }
        for(string::iterator ite = s.begin();
            ite < s.end();++ite
            )
        {

            bool match = false;
            for(vector<string>::iterator w_ite = new_words.begin(); w_ite != new_words.end(); ++w_ite)
            {
                if(compareWord(ite,s.end(), *w_ite))
                {
                    int idx = ite - s.begin();
                    int wordIdx = w_ite - new_words.begin();
                    //cout<<"idx = "<<idx << " wordIdx = "<<wordIdx<<endl;
                    wordIndices[wordIdx][idx] = 1;
                    match = true;
                }
            }
        }
         //debug(wordIndices, new_words);
        vector<int> tmp_indices(s.size(),-1);
        for(int i = 0; i < s.size();++i)
        {
            for(int j =0; j< wordIndices.size();++j)
            {
                if(wordIndices[j][i] > 0)
                {
                    tmp_indices[i] =j; 
                }
            }
        }
        //debug(tmp_indices, new_words);
        
        vector<int> rt;
        for(vector<int>::iterator ite = tmp_indices.begin(); ite != tmp_indices.end();++ite)
        {
            bool available = true;
            vector<int> tmp_flags(flags);
            //       cout<<"=========="<<endl;
            //          cout<<"iterate flags =========="<<endl;
            for(int i =0; i < words.size();++i) 
            {
                if (ite +i*word_length >= tmp_indices.end())
                {
                    available = false; 
                    break;
                }
                int idx = *(ite + i*word_length);

                //              cout<<"idx = "<<idx<<endl;
                if(idx <0)
                {
                    available = false; 
                    break;
                }
                if (tmp_flags[idx] <= 0)
                {
                    available = false; 
                    break;
                }
                tmp_flags[idx] --;
            }
            //         cout<<"check available"<<endl;
            if(available)
            {
                for(vector<int>::iterator f_ite = tmp_flags.begin(); f_ite!= tmp_flags.end();++f_ite)
                {
                    //                cout<<"f_ite = "<<*f_ite<<endl;
                    if(*f_ite != 0)
                    {
                        available =false;
                        break;
                    }
                }    
            }

            //cout<<"after check available"<<endl;
            if(available)
            {
                rt.push_back((ite-tmp_indices.begin()));
            }
        }
        return rt;
    }
}   ;