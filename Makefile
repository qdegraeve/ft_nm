all :
	@make -C nm_files/
	@make -C otool_files/
	@cp nm_files/ft_nm .
	@cp otool_files/ft_otool .
	@echo "\033[1;34m --NM_OTTOL-- :\033[m \033[1;32m DONE !\033[m"

clean :
	@make clean -C nm_files/
	@make clean -C otool_files/
	@echo "\033[1;34m --NM_OTTOL-- :\033[m \033[1;32m DELETE OBJ FILES !\033[m"

fclean : clean
	@rm -rf ft_nm
	@rm -rf ft_otool
	@make fclean -C nm_files/
	@make fclean -C otool_files/
	@echo "\033[1;34m --NM_OTTOL-- :\033[m \033[1;32m DELETE project !\033[m"

re : fclean all

.PHONY : all re clean fclean
