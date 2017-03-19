/**
 * APLT
 * < arnaud perrault />
 * barde-backoffice - Created on 17/03/2017
 */

var currModule = {
    Name: "main"
};

angular.module(currModule.Name, [
    currModule.Name + '.routes',
    currModule.Name + '.services',
    currModule.Name + '.controllers',
    //currModule.Name + '.directives'
]);

angular.module(currModule.Name).constant("CstMain", {
    name: currModule.Name
});

angular.module(currModule.Name + '').run(
    ['CstMain',
        function (Cst) {

            console.info(">>> " + Cst.name)
            console.info(Cst)
            console.info("<<< module initialized !")


        }]);

