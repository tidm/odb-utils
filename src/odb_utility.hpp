#ifndef ODB_UTILITY_HPP
#define ODB_UTILITY_HPP
#include <odb/database.hxx>
#include <odb/result.hxx>
#include <odb/query.hxx>
#include <odb/transaction.hxx>
#include <odb/exception.hxx>
#include <functional>
#include <exception.hpp>
#include <vector>
#include <list>
namespace oi {
class odb_travers {
    public :
        template <typename T, typename TY>
        static void get_def_set(odb::database* _db,std::set<TY>& o_set) {
            typedef odb::result<T> def_result;
            if (_db == NULL) {
                oi::exception ox(__FILE__,__FUNCTION__,"the db is null");
                throw ox;
            }
            try {
                odb::transaction t (_db->begin ());
                def_result def_list_result (_db->query<T> ());
                for (T& p : def_list_result) {
                    o_set.insert(p.get_key());
                }
                t.commit();
            }
            catch(odb::exception& dx) {
                oi::exception ox("std","exception",dx.what());
                ox.add_msg(__FILE__,__FUNCTION__,"unable to get def list from database");
                throw ox;
            }
            catch(std::exception& sx) {
                oi::exception ox("std","exception",sx.what());
                ox.add_msg(__FILE__,__FUNCTION__,"unable to get def list from database");
                throw ox;
            }
        }
        template <typename T,typename TY,typename TZ>
        static void get_def_map(odb::database* _db,std::map<TY,TZ>& o_map_def) {
            typedef odb::result<T> def_result;
            typedef odb::query<T>  def_query;
            if (_db == NULL) {
                oi::exception ox(__FILE__,__FUNCTION__,"the db is null");
                throw ox;
            }
            try {
                odb::transaction t (_db->begin ());
                def_result def_list_result (_db->query<T> (def_query::id > 0));
                for (T& p: def_list_result) {
                    o_map_def.insert(std::pair<std::string,int>(p.get_key(),p.get_value()));
                }
                t.commit();
            }
            catch(odb::exception& dx) {
                oi::exception ox("std","exception",dx.what());
                ox.add_msg(__FILE__,__FUNCTION__,"unable to get def list from database");
                throw ox;
            }
            catch(std::exception& sx) {
                oi::exception ox("std","exception",sx.what());
                ox.add_msg(__FILE__,__FUNCTION__,"unable to get def list from database");
                throw ox;
            }
        }


        template <typename T >
        static void travers (odb::database* _db,std::function<void(T&)> func) {
            typedef odb::result<T> def_result;
            if (_db == NULL) {
                oi::exception ox(__FILE__,__FUNCTION__,"the db is null");
                throw ox;
            }
            try {
                odb::transaction t (_db->begin ());
                def_result def_list_result (_db->query<T>());
                for (T& p: def_list_result) {
                    func(p);
                }
                t.commit();
            }
            catch (odb::exception& dx) {
                oi::exception ox("std","exception",dx.what());
                ox.add_msg(__FILE__,__FUNCTION__,"unable to travers table");
                throw ox;
            }
        }

        template <typename T >
        static void travers (odb::database* _db, odb::query<T> query,std::function<void(T&)> func ) {
            typedef odb::result<T> def_result;
            if (_db == NULL) {
                oi::exception ox(__FILE__,__FUNCTION__,"the db is null");
                throw ox;
            }
            try {
                odb::transaction t (_db->begin ());
                def_result def_list_result (_db->query<T>(query));
                for (T& p: def_list_result) {
                    func(p);
                }
                t.commit();
            }
            catch (odb::exception& dx) {
                oi::exception ox("std","exception",dx.what());
                ox.add_msg(__FILE__,__FUNCTION__,"unable to travers table");
                throw ox;
            }
        }


        template <typename T >
        static void travers (odb::database* _db, odb::query<T>& query,std::function<void(T&)> func ) {
            typedef odb::result<T> def_result;
            if (_db == NULL) {
                oi::exception ox(__FILE__,__FUNCTION__,"the db is null");
                throw ox;
            }
            try {
                odb::transaction t (_db->begin ());
                def_result def_list_result (_db->query<T>(query));
                for (T& p: def_list_result) {
                    func(p);
                }
                t.commit();
            }
            catch (odb::exception& dx) {
                oi::exception ox("std","exception",dx.what());
                ox.add_msg(__FILE__,__FUNCTION__,"unable to travers table");
                throw ox;
            }
        }
        //-----------------------------------------------------------------------------------------------------------
        template <typename T >
        static void travers (odb::database* _db,std::function<bool(T&)> func) {
            typedef odb::result<T> def_result;
            if (_db == NULL) {
                oi::exception ox(__FILE__,__FUNCTION__,"the db is null");
                throw ox;
            }
            try {
                odb::transaction t (_db->begin ());
                def_result def_list_result (_db->query<T>());
                for (T& p: def_list_result) {
                    if ( func(p) == false ) {
                        break;
                    }
                }
                t.commit();
            }
            catch (odb::exception& dx) {
                oi::exception ox("std","exception",dx.what());
                ox.add_msg(__FILE__,__FUNCTION__,"unable to travers table");
                throw ox;
            }
        }

        template <typename T >
        static void travers (odb::database* _db, odb::query<T> query,std::function<bool(T&)> func ) {
            typedef odb::result<T> def_result;
            if (_db == NULL) {
                oi::exception ox(__FILE__,__FUNCTION__,"the db is null");
                throw ox;
            }
            try {
                odb::transaction t (_db->begin ());
                def_result def_list_result (_db->query<T>(query));
                for (T& p: def_list_result) {
                    if ( func(p) == false ) {
                        break;
                    }
                }
                t.commit();
            }
            catch (odb::exception& dx) {
                oi::exception ox("std","exception",dx.what());
                ox.add_msg(__FILE__,__FUNCTION__,"unable to travers table");
                throw ox;
            }
        }


        template <typename T >
        static void travers (odb::database* _db, odb::query<T>& query,std::function<bool(T&)> func ) {
            typedef odb::result<T> def_result;
            if (_db == NULL) {
                oi::exception ox(__FILE__,__FUNCTION__,"the db is null");
                throw ox;
            }
            try {
                odb::transaction t (_db->begin ());
                def_result def_list_result (_db->query<T>(query));
                for (T& p: def_list_result) {
                    if ( func(p) == false ) {
                        break;
                    }
                }
                t.commit();
            }
            catch (odb::exception& dx) {
                oi::exception ox("std","exception",dx.what());
                ox.add_msg(__FILE__,__FUNCTION__,"unable to travers table");
                throw ox;
            }
        }
        //------------------------------------------------------------------------------
        template <typename T >
        static void travers_ex (odb::database* _db, std::function<void(T&)> func) {
            typedef odb::result<T> def_result;
            try {
                def_result def_list_result (_db->query<T>());
                for (T& p: def_list_result) {
                    func(p);
                }
            }
            catch (odb::exception& dx) {
                oi::exception ox("std","exception",dx.what());
                ox.add_msg(__FILE__,__FUNCTION__,"unable to travers table");
                throw ox;
            }
        }

        template <typename T >
        static void travers_ex (odb::database* _db,  odb::query<T>& query,std::function<void(T&)> func ) {
            typedef odb::result<T> def_result;
            try {
                def_result def_list_result (_db->query<T>(query));
                for (T& p: def_list_result) {
                    func(p);
                }
            }
            catch (odb::exception& dx) {
                oi::exception ox("std","exception",dx.what());
                ox.add_msg(__FILE__,__FUNCTION__,"unable to travers table");
                throw ox;
            }
        }

        template <typename T >
        static void travers_ex (odb::database* _db, std::function<bool(T&)> func) {
            typedef odb::result<T> def_result;
            try {
                def_result def_list_result (_db->query<T>());
                for (T& p: def_list_result) {
                    if ( func(p) == false ) {
                        break;
                    }
                }
            }
            catch (odb::exception& dx) {
                oi::exception ox("std","exception",dx.what());
                ox.add_msg(__FILE__,__FUNCTION__,"unable to travers table");
                throw ox;
            }
        }

        template <typename T >
        static void travers_ex (odb::database* _db,  odb::query<T> query,std::function<bool(T&)> func ) {
            typedef odb::result<T> def_result;
            try {
                def_result def_list_result (_db->query<T>(query));
                for (T& p: def_list_result) {
                    if ( func(p) == false ) {
                        break;
                    }
                }
            }
            catch (odb::exception& dx) {
                oi::exception ox("std","exception",dx.what());
                ox.add_msg(__FILE__,__FUNCTION__,"unable to travers table");
                throw ox;
            }
        }


        template <typename T >
        static void travers_ex (odb::database* _db, odb::query<T>& query,std::function<bool(T&)> func ) {
            typedef odb::result<T> def_result;
            try {
                def_result def_list_result (_db->query<T>(query));
                for (T& p: def_list_result) {
                    if ( func(p) == false ) {
                        break;
                    }
                }
            }
            catch (odb::exception& dx) {
                oi::exception ox("std","exception",dx.what());
                ox.add_msg(__FILE__,__FUNCTION__,"unable to travers table");
                throw ox;
            }
        }
        //--------------------------------------------------------------------------------
        template <typename T>
        static void travers (odb::database* _db,std::vector<T>& i_vec) {
            typedef odb::result<T> def_result;
            if (_db == NULL) {
                oi::exception ox(__FILE__,__FUNCTION__,"the db is null");
                throw ox;
            }
            try {
                odb::transaction t (_db->begin ());
                def_result def_list_result (_db->query<T>());
                for (T& p: def_list_result) {
                    i_vec.push_back(p);
                }
                t.commit();
            }
            catch (odb::exception& dx) {
                oi::exception ox("std","exception",dx.what());
                ox.add_msg(__FILE__,__FUNCTION__,"unable to travers table");
                throw ox;
            }
        }
        template <typename T>
        static void travers (odb::database* _db,std::list<T>& i_list) {
            typedef odb::result<T> def_result;
            if (_db == NULL) {
                oi::exception ox(__FILE__,__FUNCTION__,"the db is null");
                throw ox;
            }
            try {
                odb::transaction t (_db->begin ());
                def_result def_list_result (_db->query<T>());
                for (T& p: def_list_result) {
                    i_list.push_back(p);
                }
                t.commit();
            }
            catch (odb::exception& dx) {
                oi::exception ox("std","exception",dx.what());
                ox.add_msg(__FILE__,__FUNCTION__,"unable to travers table");
                throw ox;
            }
        }

        template <typename T >
        static void travers (odb::database* _db, odb::query<T> query,std::vector<T>& i_vec) {
            typedef odb::result<T> def_result;
            if (_db == NULL) {
                oi::exception ox(__FILE__,__FUNCTION__,"the db is null");
                throw ox;
            }
            try {
                odb::transaction t (_db->begin ());
                def_result def_list_result (_db->query<T>(query));
                for (T& p: def_list_result) {
                    i_vec.push_back(p);
                }
                t.commit();
            }
            catch (odb::exception& dx) {
                oi::exception ox("std","exception",dx.what());
                ox.add_msg(__FILE__,__FUNCTION__,"unable to travers table");
                throw ox;
            }
        }

        template <typename T >
        static void travers (odb::database* _db, odb::query<T> query,std::list<T>& i_list) {
            typedef odb::result<T> def_result;
            if (_db == NULL) {
                oi::exception ox(__FILE__,__FUNCTION__,"the db is null");
                throw ox;
            }
            try {
                odb::transaction t (_db->begin ());
                def_result def_list_result (_db->query<T>(query));
                for (T& p: def_list_result) {
                    i_list.push_back(p);
                }
                t.commit();
            }
            catch (odb::exception& dx) {
                oi::exception ox("std","exception",dx.what());
                ox.add_msg(__FILE__,__FUNCTION__,"unable to travers table");
                throw ox;
            }
        }
        template <typename T >
        static void travers (odb::database* _db, odb::query<T>& query, std::vector<T>& i_vec) {
            typedef odb::result<T> def_result;
            if (_db == NULL) {
                oi::exception ox(__FILE__,__FUNCTION__,"the db is null");
                throw ox;
            }
            try {
                odb::transaction t (_db->begin ());
                def_result def_list_result (_db->query<T>(query));
                for (T& p: def_list_result) {
                    i_vec.push_back(p);
                }
                t.commit();
            }
            catch (odb::exception& dx) {
                oi::exception ox("std","exception",dx.what());
                ox.add_msg(__FILE__,__FUNCTION__,"unable to travers table");
                throw ox;
            }
        }
        template <typename T >
        static void travers (odb::database* _db, odb::query<T>& query, std::list<T>& i_list) {
            typedef odb::result<T> def_result;
            if (_db == NULL) {
                oi::exception ox(__FILE__,__FUNCTION__,"the db is null");
                throw ox;
            }
            try {
                odb::transaction t (_db->begin ());
                def_result def_list_result (_db->query<T>(query));
                for (T& p: def_list_result) {
                    i_list.push_back(p);
                }
                t.commit();
            }
            catch (odb::exception& dx) {
                oi::exception ox("std","exception",dx.what());
                ox.add_msg(__FILE__,__FUNCTION__,"unable to travers table");
                throw ox;
            }
        }

        //-------------------------------------------------------------------------------------------

        template <typename T>
        static void travers_ex (odb::database* _db, std::vector<T>& i_vec) {
            typedef odb::result<T> def_result;
            i_vec.clear();
            try {
                def_result def_list_result (_db->query<T>());
                for (T& p: def_list_result) {
                    i_vec.push_back(p);
                }
            }
            catch (odb::exception& dx) {
                oi::exception ox("std","exception",dx.what());
                ox.add_msg(__FILE__,__FUNCTION__,"unable to travers table");
                throw ox;
            }
        }
        template <typename T>
        static void travers_ex (odb::database* _db, std::list<T>& i_list) {
            typedef odb::result<T> def_result;
            try {
                def_result def_list_result (_db->query<T>());
                for (T& p: def_list_result) {
                    i_list.push_back(p);
                }
            }
            catch (odb::exception& dx) {
                oi::exception ox("std","exception",dx.what());
                ox.add_msg(__FILE__,__FUNCTION__,"unable to travers table");
                throw ox;
            }
        }

        template <typename T >
        static void travers_ex (odb::database* _db, odb::query<T> query,std::vector<T>& i_vec) {
            typedef odb::result<T> def_result;
            try {
                def_result def_list_result (_db->query<T>(query));
                for (T& p: def_list_result) {
                    i_vec.push_back(p);
                }
            }
            catch (odb::exception& dx) {
                oi::exception ox("std","exception",dx.what());
                ox.add_msg(__FILE__,__FUNCTION__,"unable to travers table");
                throw ox;
            }
        }

        template <typename T >
        static void travers_ex (odb::database* _db, odb::query<T> query,std::list<T>& i_list) {
            typedef odb::result<T> def_result;
            try {
                def_result def_list_result (_db->query<T>(query));
                for (T& p: def_list_result) {
                    i_list.push_back(p);
                }
            }
            catch (odb::exception& dx) {
                oi::exception ox("std","exception",dx.what());
                ox.add_msg(__FILE__,__FUNCTION__,"unable to travers table");
                throw ox;
            }
        }
        template <typename T >
        static void travers_ex (odb::database* _db, odb::query<T>& query, std::vector<T>& i_vec) {
            typedef odb::result<T> def_result;
            try {
                def_result def_list_result (_db->query<T>(query));
                for (T& p: def_list_result) {
                    i_vec.push_back(p);
                }
            }
            catch (odb::exception& dx) {
                oi::exception ox("std","exception",dx.what());
                ox.add_msg(__FILE__,__FUNCTION__,"unable to travers table");
                throw ox;
            }
        }
        template <typename T >
        static void travers_ex (odb::database* _db,odb::query<T>& query, std::list<T>& i_list) {
            typedef odb::result<T> def_result;
            try {
                def_result def_list_result (_db->query<T>(query));
                for (T& p: def_list_result) {
                    i_list.push_back(p);
                }
            }
            catch (odb::exception& dx) {
                oi::exception ox("std","exception",dx.what());
                ox.add_msg(__FILE__,__FUNCTION__,"unable to travers table");
                throw ox;
            }
        }

};
}

#endif // ODB_UTILITY_HPP
