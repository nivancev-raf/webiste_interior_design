package nikolalukatrening.Notifikacioni_servis.config;

import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.web.servlet.config.annotation.CorsRegistry;
import org.springframework.web.servlet.config.annotation.WebMvcConfigurer;

@Configuration
public class WebConfig implements WebMvcConfigurer {

    @Override
    public void addCorsMappings(CorsRegistry registry) {
        registry.addMapping("/api/notifications/sendEmail") // Use the appropriate path pattern
                .allowedOrigins("*")
                .allowedMethods("POST", "GET", "OPTIONS", "DELETE")
                .allowedHeaders("Content-Type", "Access-Control-Allow-Headers", "Authorization", "X-Requested-With")
                .allowCredentials(false)
                .maxAge(3600);
    }
}
