package com.tictac.TicTacServer.beans.common;

import com.tictac.TicTacServer.Player;
import com.tictac.TicTacServer.interfaces.GameRepository;
import org.springframework.stereotype.Repository;

import javax.persistence.*;
import javax.persistence.criteria.CriteriaBuilder;
import javax.persistence.criteria.CriteriaQuery;
import javax.persistence.criteria.Root;
import java.util.List;

//@Repository
public class SqlJpaRepository implements GameRepository {

    SqlJpaRepository() {
        System.out.println("SqlJpaRepository constructor");
    }

    public Player login(String login, String password) {
        System.out.println("SqlJpaRepository login");
        return null;
    }
/*
    private EntityManagerFactory factory;

    @PersistenceContext
    EntityManager entityManager;

    public GameRepository() {
        this.factory = Persistence.createEntityManagerFactory("EntityMappings");
    }

    @Override
    protected void finalize() throws Throwable {
        this.factory.close();
    }

    public boolean authenticate(String login, String password) {
        EntityManager manager = null;
        EntityTransaction transaction = null;
        UserEntity user = null;
        try
        {
            manager = this.factory.createEntityManager();
            transaction = manager.getTransaction();
            transaction.begin();

            CriteriaBuilder builder = manager.getCriteriaBuilder();
            CriteriaQuery<UserEntity> criteria = builder.createQuery(UserEntity.class);
            Root<UserEntity> userRoot = criteria.from(UserEntity.class);
            criteria.select(userRoot);
            criteria.where(builder.equal(userRoot.get("login"), login));
            user = manager.createQuery(criteria).getSingleResult();

            transaction.commit();
        }
        catch(Exception e)
        {
            if(transaction != null && transaction.isActive())
                transaction.rollback();
        }
        finally
        {
            if(manager != null && manager.isOpen())
                manager.close();
        }
        return (user != null);
    }
*/
}
