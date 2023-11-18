#ifndef PP_BANK_ACCOUNTLIST_H
#define PP_BANK_ACCOUNTLIST_H

#include<iostream>
#include<vector>

class account_list {
public:
    class account {
    protected:
        long m_id;
        std::string m_holder_name;
        std::string m_holder_pesel;
        bool m_deleted;
    public:
        account(long id, std::string holder_name, std::string holder_pesel, bool deleted);
        long id() const;
        std::string name();
        std::string pesel();
        bool deleted() const;
    };

    bool add_or_modify_account(const account&t);
    long get_account_vector_index(long id) const;
    account* get_account(long id);
    bool delete_account(long id);
    long get_next_account_id() const;
    bool account_exists(long id) const;
    const std::vector<account>* get_accounts() const;
private:
    std::vector<account> m_list;
};

typedef account_list::account account;


#endif //PP_BANK_ACCOUNTLIST_H
