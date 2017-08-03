package com.tictac.TicTacServer.config.annotation;

import org.springframework.stereotype.Controller;

import java.lang.annotation.*;

@Target({ ElementType.TYPE })
@Retention(RetentionPolicy.RUNTIME)
@Documented
@Controller
public @interface HomePage {
    String value() default "";
}
