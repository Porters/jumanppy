#/bin/sh

export DOMAIN=ihai
export REPOS=ai-common
export CODEARTIFACT_REPOSITORY_URL=$(aws codeartifact get-repository-endpoint --domain $DOMAIN --repository $REPOS --format pypi --query 'repositoryEndpoint' --output text)
export CODEARTIFACT_USER=aws
export CODEARTIFACT_AUTH_TOKEN=$(aws codeartifact get-authorization-token --domain $DOMAIN --query 'authorizationToken' --output text)

# Todo: use poetry publish when aws support.
# (currently it return 401 error)
pip install twine
aws codeartifact login --tool twine --domain $DOMAIN --repository $REPOS

\twine upload --repository codeartifact dist/*
